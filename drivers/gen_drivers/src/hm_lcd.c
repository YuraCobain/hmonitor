#include "hm_led.h"
#include "main.h"
#include "stm32f429i_discovery_lcd.h"
#include "color2.h"
#include "save.h"

#define LCD_FRAME_BUFFER_LAYER0 (LCD_FRAME_BUFFER+0x130000)
#define LCD_FRAME_BUFFER_LAYER1  LCD_FRAME_BUFFER
#define CONVERTED_FRAME_BUFFER  (LCD_FRAME_BUFFER+0x260000)

static uint8_t curr_line = 0;

void hm_lcd_init(void)
{
    /* Initialize the LCD */
    BSP_LCD_Init();

    /* Layer2 Init */
    BSP_LCD_LayerDefaultInit(1, LCD_FRAME_BUFFER_LAYER1);
    /* Set Foreground Layer */
    BSP_LCD_SelectLayer(1);
    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);  
    BSP_LCD_SetColorKeying(1, LCD_COLOR_WHITE);
    BSP_LCD_SetLayerVisible(1, DISABLE);

    /* Layer1 Init */
    BSP_LCD_LayerDefaultInit(0, LCD_FRAME_BUFFER_LAYER0);

    /* Set Foreground Layer */
    BSP_LCD_SelectLayer(0);

    /* Enable The LCD */
    BSP_LCD_DisplayOn();
    BSP_LCD_SetFont(&Font12);
    
    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);
}

/**
* @brief  Draw the menu.
* @param  None
* @retval None
    */
void hm_lcd_menu(void)
{ 
    /* Set background Layer */
    BSP_LCD_SelectLayer(0);

    /* Clear the LCD */
    BSP_LCD_Clear(LCD_COLOR_WHITE);  

    
    BSP_LCD_SelectLayer(1);
}

#define MAX_NUM_LINES 20
void hm_lcd_line_put(uint16_t line, uint8_t *str)
{
    if (curr_line > MAX_NUM_LINES)
    {
        curr_line = 0;
          /* Clear the LCD */
        BSP_LCD_Clear(LCD_COLOR_WHITE); 
    }
    BSP_LCD_DisplayStringAtLine(curr_line++, str);
}
