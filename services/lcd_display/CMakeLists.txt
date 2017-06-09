SET(GEN_DRIVERS_SRCS
    hm_led.c
    hm_lcd.c
    hm_uart.c
)
ADD_LIBRARY(gen_drivers OBJECT ${GEN_DRIVERS_SRCS})

STM32_SET_CHIP_DEFINITIONS(gen_drivers ${STM32_CHIP_TYPE})
