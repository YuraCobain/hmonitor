set(CO2_MONITOR_SRCS
    src/co2_monitor.c
)

add_library(co2_monitor STATIC ${CO2_MONITOR_SRCS})

target_include_directories(co2_monitor PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc>
    PRIVATE src)

STM32_SET_CHIP_DEFINITIONS(co2_monitor ${STM32_CHIP_TYPE})
