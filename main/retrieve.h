#include <sys/param.h>
// #include "esp_netif.h"
#include <esp_http_client.h>
#include "esp_tls.h"
#include "esp_log.h"

#include "lwip/err.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "lwip/netdb.h"
#include "lwip/dns.h"
#include "cJSON.h"


static const char *TAG = "HTTP_CLIENT";
void parse_response(char *json_Str);


char *output_buffer;  // Buffer to store response of http request from event handler
int output_len=0;       // Stores number of bytes read
esp_err_t _http_event_handler(esp_http_client_event_t *evt)
{
    esp_http_client_event_id_t evn_id = evt->event_id;
    // ESP_LOGI(TAG, "HTTP handling... with event id :%d", evn_id);

    switch (evn_id){
    case HTTP_EVENT_ERROR:
        ESP_LOGI(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_HEADER_SENT:
            ESP_LOGI(TAG, "HTTP_EVENT_HEADER_SENT");
            break;
    case HTTP_EVENT_ON_HEADER:
            ESP_LOGI(TAG, "HTTP_EVENT_ON_HEADER, key=%s, value=%s", evt->header_key, evt->header_value);
            break;
    case HTTP_EVENT_ON_DATA:
        output_len = evt->data_len;

        ESP_LOGI(TAG, "HTTP_EVENT_ON_DATA: , len=%d",output_len);
        if (output_buffer != NULL && strlen(output_buffer) >0){
            free(output_buffer);
        }

        output_buffer  = (char *) malloc(sizeof(char) * (output_len));

        memcpy(&output_buffer[0], (char *) evt->data, output_len);

        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_FINISH");
        if (output_buffer != NULL) {
            parse_response(output_buffer);
            free(output_buffer);
            output_buffer = NULL;
        }
        output_len = 0;
        break;
    case HTTP_EVENT_DISCONNECTED:
        ESP_LOGI(TAG, "HTTP_EVENT_ON_DISCONNECTED");
        break;
    default:
        break;
    }

    return ESP_OK;
}

esp_err_t err;

// Function to fetch data from ThingSpeak and parse the response
void fetch_data_from_thingspeak(void *pvParameters)
{
    // light_val=-1;
    // ThingSpeak API URL
    char thingspeak_url[100] = "https://api.thingspeak.com/channels/2346639/fields/1.json?results=2";

    // Configuration for the HTTP client
    esp_http_client_config_t config = {
        .url = thingspeak_url,
        .port = 80,
        .auth_type = HTTP_AUTH_TYPE_NONE,
        .method = HTTP_METHOD_GET,
        .event_handler = _http_event_handler,
    };

    // Initialize the HTTP client with the specified configuration
    esp_http_client_handle_t client = esp_http_client_init(&config);

    while (1)
    {   
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        ESP_LOGI(TAG, "HTTP new request...");
        err = esp_http_client_perform(client);
        
        
        if (err != ESP_OK)
            ESP_LOGI(TAG, "HTTP Client perform Failed !!");
        else
            ESP_LOGI(TAG, "Data collected from HTTP Request");

    }
    
    // Clean up and release resources associated with the HTTP client
    esp_http_client_cleanup(client);

    // Delete the current FreeRTOS task
    vTaskDelete(NULL);
}

esp_err_t JSON_Print(cJSON *element) {
	if (element->type == cJSON_Invalid) ESP_LOGI(TAG, "cJSON_Invalid");
	if (element->type == cJSON_False) ESP_LOGI(TAG, "cJSON_False");
	if (element->type == cJSON_True) ESP_LOGI(TAG, "cJSON_True");
	if (element->type == cJSON_NULL) ESP_LOGI(TAG, "cJSON_NULL");
	if (element->type == cJSON_Number) ESP_LOGI(TAG, "cJSON_Number int=%d double=%f", element->valueint, element->valuedouble);
	if (element->type == cJSON_String) ESP_LOGI(TAG, "cJSON_String string=%s", element->valuestring);
	if (element->type == cJSON_Array) ESP_LOGI(TAG, "cJSON_Array");
	if (element->type == cJSON_Object) {
		ESP_LOGI(TAG, "cJSON_Object");
		cJSON *child_element = NULL;
		cJSON_ArrayForEach(child_element, element) {
			JSON_Print(child_element);
		}
	}
	if (element->type == cJSON_Raw) ESP_LOGI(TAG, "cJSON_Raw");

    return ESP_OK;
}

void parse_response(char *json_Str){

        // ESP_LOGI(TAG, "Parsing Data: %sOf len %d", json_Str, strlen(json_Str));

        cJSON *root = cJSON_Parse(json_Str);
        cJSON *feeds = cJSON_GetObjectItem(root, "feeds");

        // JSON_Print(feeds);
        cJSON *obj = cJSON_GetArrayItem(feeds, 1);
        // JSON_Print(obj);
        cJSON *field1 = cJSON_GetObjectItem(obj, "field1");
        err = JSON_Print(field1);
        if(err==ESP_OK && field1->type== cJSON_String){  
                light_str = field1->valuestring;
                light_val = atof(field1->valuestring);
                ESP_LOGI(TAG, "Obtained Field1: %.2f", light_val);
        }
        else
            ESP_LOGI(TAG, "Obtaining field1 failed");
}

