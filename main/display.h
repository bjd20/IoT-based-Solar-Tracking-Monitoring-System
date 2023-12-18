#include <ssd1306.h>

SSD1306_t dev;
#define DISP_TAG "SSD1306"

void display_init(){
#if CONFIG_I2C_INTERFACE
	ESP_LOGI(DISP_TAG, "INTERFACE is i2c");
	ESP_LOGI(DISP_TAG, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(DISP_TAG, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(DISP_TAG, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_FLIP
	dev._flip = true;
	ESP_LOGW(DISP_TAG, "Flip upside down");
#endif
}

void display_test(){
	#if CONFIG_SSD1306_128x32
	ESP_LOGI(DISP_TAG, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
	#endif // CONFIG_SSD1306_128x32

    ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
    ssd1306_display_text_x3(&dev, 0, "Test...", 5, false);

    vTaskDelay(1000 / portTICK_PERIOD_MS);
}

void display_show(){
	ssd1306_clear_screen(&dev, false);
	char *txt1 = "Solar Tracking";
	char *txt2 = "System";
	char txt3[20]= "Light: ";

	strcat(txt3, light_str);
	// ssd1306_display_text(&dev, 0, "Hello IITD", 10, false);
	ssd1306_display_text(&dev, 0, txt1 ,strlen(txt1), false);
    ssd1306_display_text(&dev, 1, txt2 ,strlen(txt2), false);
	ssd1306_display_text(&dev, 2, txt3 ,strlen(txt3), false);
	
	vTaskDelay(1000 / portTICK_PERIOD_MS);
}
