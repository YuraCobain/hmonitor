SET(CMAKE_SYSTEM_NAME Linux)
SET(CMAKE_C_FLAGS "-g -gdwarf-version")

PROJECT(hmonitor)

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ENABLE_LANGUAGE(ASM)
SET( CMAKE_EXPORT_COMPILE_COMMANDS ON )
FIND_PACKAGE(CMSIS REQUIRED)
FIND_PACKAGE(STM32BSP COMPONENTS lcd sdram ili9341 REQUIRED)
FIND_PACKAGE(STM32HAL COMPONENTS gpio tim spi sdram fmc ltdc dma dma2d uart rcc pwr REQUIRED)
FIND_PACKAGE(FreeRTOS COMPONENTS kernel REQUIRED)

INCLUDE_DIRECTORIES(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/middleware/ipc/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/drivers/gen_drivers/inc
    ${CMSIS_INCLUDE_DIRS}
    ${STM32HAL_INCLUDE_DIR}
    ${STM32BSP_INCLUDE_DIR}
    ${FREERTOS_kernel_INCLUDE_DIR}
)

ADD_SUBDIRECTORY(drivers)
ADD_SUBDIRECTORY(services)
ADD_SUBDIRECTORY(middleware)

SET(PROJECT_SOURCES
    src/main.c
    src/stm32f4xx_hal_timebase_tim.c
    src/stm32f4xx_it.c
    middleware/ipc/src/hm_msg_ch.c
)

ADD_EXECUTABLE(${CMAKE_PROJECT_NAME}
    ${PROJECT_SOURCES}
    ${CMSIS_SOURCES}
    ${STM32HAL_SOURCES}
    ${STM32BSP_SOURCES}
    ${FREERTOS_kernel_SOURCES}
)

TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}
    lcd_service
    co2_monitor
    hm_drivers
)

STM32_SET_TARGET_PROPERTIES(${CMAKE_PROJECT_NAME})
STM32_ADD_HEX_BIN_TARGETS(${CMAKE_PROJECT_NAME})
