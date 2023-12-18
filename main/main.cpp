#include "Arduino.h"
#include "servoCTRL.h"
#include <lwip/sockets.h>

double light_val=0;
char *light_str = "0.0";
extern "C"
{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "freertos/FreeRTOS.h"
	#include "freertos/task.h"
	#include "esp_log.h"
	#include "display.h"
	#include "font8x8_basic.h"
	#include "connect.h"
	#include "retrieve.h"
}


#define TAG "Solar-Tracking"

esp_err_t wifi_status = WIFI_FAILURE;


extern "C"
{
	void display_show(void);
	void wifi_init(void);
	void app_main(void);
}



void app_main(void){
	//initialize storage
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
      ESP_ERROR_CHECK(nvs_flash_erase());
      ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

		for (int i = 3; i >= 0; i--) {
        printf("Starting in %d seconds...\n", i);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    printf("Starting now.\n");
	vTaskDelay(3000 / portTICK_PERIOD_MS);
	// Serial.begin(115200);
	// vTaskDelay(5000/ portTICK_PERIOD_MS);
	// Serial.println("Serial monitor is Working...");

	wifi_init();
    display_init();
    display_test();
	

	Serial1.begin(1000000, SERIAL_8N1, S_RXD, S_TXD);
  	sc.pSerial = &Serial1;
  	delay(1000);

	if (wifi_status == WIFI_SUCCESS)
	{
		// fetch_data_from_thingspeak(NULL);
		xTaskCreate(&fetch_data_from_thingspeak, "receive_data_from_thingspeak", 8192, NULL, 3, NULL);
	}

	servoPing();

	while(1){
		display_show();
		servoPosTo(light_val);
	}
}


void wifi_init(){
    // connect to wireless AP
	wifi_status = connect_wifi();
	if (WIFI_SUCCESS != wifi_status)
	{
		ESP_LOGI(TAG, "Failed to associate to AP, dying...");
		return;
	}
}

