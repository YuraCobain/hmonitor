#ifndef __LED_H__
#define __LED_H__
typedef enum {
    HM_LED1,
    HM_LED2,
} hm_led_t;

void hm_led_init(hm_led_t led);
void hm_led_deinit(hm_led_t led);
void hm_led_on(hm_led_t led);
void hm_led_off(hm_led_t led);
void hm_led_toggle(hm_led_t led);

#endif
