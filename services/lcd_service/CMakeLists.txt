set(LCD_DISPLAY_SRCS
    src/lcd_service.c
)

add_library(lcd_service STATIC ${LCD_DISPLAY_SRCS})
target_include_directories(lcd_service PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc>
    PRIVATE src)

STM32_SET_CHIP_DEFINITIONS(lcd_service ${STM32_CHIP_TYPE})
