#include "lcd_service.h"
#include "co2_monitor.h"
#include "hm_msg_ch.h"
#include "hm_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "main.h"
#include "hm_lcd.h"

static void vLCDService(void *arg);

hm_ret_t lcd_service_start(hm_msg_ch_t *ch)
{ 
    hm_lcd_init();
    hm_led_toggle(HM_LED2);
    hm_lcd_line_put(1, (uint8_t *)"[i] lcd_init ok");
    xTaskCreate(vLCDService, "LCD Service", configMINIMAL_STACK_SIZE, ch, 2, NULL);
    return HM_OK;
}

static void vLCDService(void *arg)
{
    hm_msg_ch_t* ch = (hm_msg_ch_t *)arg;
    msg_t *msg = NULL;

    while(1)
    {
        while (hm_msg_ch_recv(ch, msg) == pdPASS)
        {
            hm_lcd_line_put(1, (uint8_t *)"msg");
        }
        hm_led_toggle(HM_LED1);
        vTaskDelay(5000);
    }
}
