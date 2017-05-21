#include "hm_led.h"
#include "main.h"
#include "stdint.h"

#define MAX_NUM_LEDS 2
uint32_t hm_led_map[MAX_NUM_LEDS] = { LED3, LED4 };

void hm_led_init(hm_led_t led)
{
    BSP_LED_Init(hm_led_map[led]);
}

void hm_led_deinit(hm_led_t led)
{
    /* BSP_LED_DeInit(hm_led_map[led]); */
}

void hm_led_on(hm_led_t led)
{
    BSP_LED_On(hm_led_map[led]);
}

void hm_led_off(hm_led_t led)
{
    BSP_LED_Off(hm_led_map[led]);
}

void hm_led_toggle(hm_led_t led)
{
    BSP_LED_Toggle(hm_led_map[led]);
}
