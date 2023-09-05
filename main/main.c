#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "ssd1306.h"
#include "font8x8_basic.h"

#define lcd_tag "SSD1306"

void app_main(void)
{
    display_init();
    display_test();
    display_show();
}

SSD1306_t dev;
int center, top, bottom;
char lineChar[20];

void display_init(){
    
#if CONFIG_I2C_INTERFACE
	ESP_LOGI(tag, "INTERFACE is i2c");
	ESP_LOGI(tag, "CONFIG_SDA_GPIO=%d",CONFIG_SDA_GPIO);
	ESP_LOGI(tag, "CONFIG_SCL_GPIO=%d",CONFIG_SCL_GPIO);
	ESP_LOGI(tag, "CONFIG_RESET_GPIO=%d",CONFIG_RESET_GPIO);
	i2c_master_init(&dev, CONFIG_SDA_GPIO, CONFIG_SCL_GPIO, CONFIG_RESET_GPIO);
#endif // CONFIG_I2C_INTERFACE

#if CONFIG_FLIP
	dev._flip = true;
	ESP_LOGW(tag, "Flip upside down");
#endif

}

void display_test(){
	#if CONFIG_SSD1306_128x32
	ESP_LOGI(tag, "Panel is 128x32");
	ssd1306_init(&dev, 128, 32);
	#endif // CONFIG_SSD1306_128x32

    ssd1306_clear_screen(&dev, false);
	ssd1306_contrast(&dev, 0xff);
    ssd1306_display_text_x3(&dev, 0, "Hello", 5, false);

    vTaskDelay(3000 / portTICK_PERIOD_MS);
}

void display_show(){
    top = 1;
	center = 1;
	bottom = 4;
	ssd1306_display_text(&dev, 0, "Hello IITD", 10, false);
	ssd1306_display_text(&dev, 1, "Solar Tracking",14, false);
    ssd1306_display_text(&dev, 2, "     &     ", 11, false);
	ssd1306_display_text(&dev, 3, "Monitoring System", 17, false);

	vTaskDelay(3000 / portTICK_PERIOD_MS);
}