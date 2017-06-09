#include "co2_monitor.h"
#include "co2_sensor.h"
#include "hm_msg_ch.h"
#include "hm_led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "string.h"
#include "main.h"

static void vCO2Monitor(void *arg);

hm_ret_t co2_monitor_start(hm_msg_ch_t *ch)
{
    hm_ret_t ret = HM_OK;

    if ((ret = co2_sensor_init()))
    {
        goto Error;
    }

    xTaskCreate(vCO2Monitor, "LCD Service", 4*configMINIMAL_STACK_SIZE, ch, 2, NULL);

Error:
    return ret;
}

static void vCO2Monitor(void *arg)
{
    static uint8_t msg[32];
    uint16_t co2_ppm;
    hm_msg_ch_t *ch = (hm_msg_ch_t *)arg;
    hm_ret_t ret = HM_OK;
   
    while(1)
    {
        hm_led_toggle(HM_LED1);
        memset(&msg, 0, 32);
        co2_ppm = 0;

        if ((ret = co2_sensor_val_get(&co2_ppm))) {
            sprintf((char *)&msg, "[err] : get_co2_val: %u", ret);
        }
        else {
            sprintf((char *)&msg, "[ok] :  get_co2_val: %u", co2_ppm);
        }

        hm_msg_ch_send(ch, (uint32_t *)&msg);
        hm_led_toggle(HM_LED1);
        vTaskDelay(5000);
    }
}
