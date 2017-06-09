#ifndef __HM_LCD_H__
#define __HM_LCD_H__

void hm_lcd_init(void);
void hm_lcd_menu(void);
void hm_lcd_line_put(uint16_t line, uint8_t *str);

#endif
