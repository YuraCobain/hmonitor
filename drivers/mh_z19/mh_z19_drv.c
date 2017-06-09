#include "main.h"
#include "co2_sensor.h"
#include "hm_uart.h"
#include "string.h"

#define MH_Z19_CMD_LEN 9u
#define DEFAULT_TIMEOUT 1000u
#define CRC_IDX 8u
#define GAS_VAL_HI_IDX 2u
#define GAS_VAL_LOW_IDX 3u

typedef struct {
    hm_uart_idx_t uart_idx;
    uint8_t resp[MH_Z19_CMD_LEN];
    uint32_t timeout;
    /* TODO: separate struct and API to get it */
    uint32_t tx_error;
    uint32_t rx_error;
    uint32_t crc_error;
} mh_z19_drv_t;

typedef struct {
    uint8_t cmd[MH_Z19_CMD_LEN];
} mh_z19_cmd_list_t;

typedef enum {
    GAS_LEVEL_READ,
    CALIB_ZERO_POINT,
    CALIB_SPAN_POINT,
    NUM_OF_CMDS
} mh_z19_cmd_enum_t; 

static mh_z19_drv_t mh_z19_driver = {
    .uart_idx = HM_UART1_IDX,
    .timeout = DEFAULT_TIMEOUT,
    .crc_error = 0,
    .rx_error = 0,
    .tx_error = 0,
};

static mh_z19_cmd_list_t mh_z19_cmds[NUM_OF_CMDS] = {
     [GAS_LEVEL_READ] = {
         .cmd = {0xFF,0x01,0x86,0x00,0x00,0x00,0x00,0x00,0x79},
     }
};

static inline uint8_t mhxx_crc_calc(uint8_t *data)
{
    uint8_t i;
    uint8_t crc = 0;

    for (i = 1; i < CRC_IDX; i++)
        crc += data[i];

    return (0xff - crc) + 1;
}

hm_ret_t co2_sensor_init(void)
{
    return hm_uart_init(mh_z19_driver.uart_idx);
}

hm_ret_t co2_sensor_uninit(void)
{
    return 0; /* hm_uart_deinit(mh_z19_driver.uart_idx); */ 
}

hm_ret_t co2_sensor_val_get(uint16_t *gas_val)
{
    uint8_t ret;

    memset(&mh_z19_driver.resp, 0, MH_Z19_CMD_LEN);
    if (hm_uart_send(mh_z19_driver.uart_idx, (uint8_t *)mh_z19_cmds[GAS_LEVEL_READ].cmd,
                MH_Z19_CMD_LEN, mh_z19_driver.timeout))
    {
        ret = HM_TX_ERR;
        mh_z19_driver.tx_error++;
        goto Exit;
    }
    
    if (hm_uart_recv(mh_z19_driver.uart_idx, (uint8_t *)mh_z19_driver.resp,
              MH_Z19_CMD_LEN, mh_z19_driver.timeout))
    {
        ret = HM_RX_ERR;
        mh_z19_driver.rx_error++;
        goto Exit;
    }

    if (!(mh_z19_driver.resp[CRC_IDX] == mhxx_crc_calc((uint8_t *)mh_z19_driver.resp)))
    {
        ret = HM_CRC_ERR;
        mh_z19_driver.crc_error++;
        goto Exit;
    }

    *gas_val = (mh_z19_driver.resp[GAS_VAL_HI_IDX] << 8 | mh_z19_driver.resp[GAS_VAL_LOW_IDX]);

    ret = HM_OK;
Exit:
    
    return ret;
}

