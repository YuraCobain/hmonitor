#include "lcd_service.h"
#include "co2_monitor.h"
#include "hm_msg_ch.h"
#include "hm_led.h"
#include "task.h"
#include "string.h"
#include "main.h"
#include "hm_lcd.h"


void vLCDService(void *arg)
{
    QueueHandle_t xQ = (QueueHandle_t)arg;
    msg_t *msg = NULL;

    hm_lcd_init();
    hm_lcd_line_put(1, (uint8_t *)"[i] lcd_init ok");

    while(1)
    {
        hm_led_toggle(HM_LED1);
        hm_lcd_line_put(1, (uint8_t *)"[i] lcd alive");
        vTaskDelay(5000);
    }
}
