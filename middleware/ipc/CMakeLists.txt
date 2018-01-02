set(HM_IPC_SRCS
    src/hm_msg_ch.c
)

add_library(hm_broker STATIC ${HM_IPC_SRCS})

target_include_directories(hm_broker PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/inc>
    $<INSTALL_INTERFACE:inc>
    PRIVATE src)


STM32_SET_CHIP_DEFINITIONS(hm_broker ${STM32_CHIP_TYPE})
