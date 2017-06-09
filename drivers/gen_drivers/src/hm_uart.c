#include "main.h"
#include "stm32f4xx_hal.h"
#include "hm_uart.h"

typedef struct {
    UART_HandleTypeDef huart;
} hm_uart_drv_t;

static hm_uart_drv_t uart_drv[NUM_OF_UARTS] = {
    [HM_UART1_IDX] = {
        .huart.Instance = USART1,
        .huart.Init.BaudRate     = 9600,
        .huart.Init.WordLength   = UART_WORDLENGTH_8B,
        .huart.Init.StopBits     = UART_STOPBITS_1,
        .huart.Init.Parity       = UART_PARITY_NONE,
        .huart.Init.HwFlowCtl    = UART_HWCONTROL_NONE,
        .huart.Init.Mode         = UART_MODE_TX_RX,
        .huart.Init.OverSampling = UART_OVERSAMPLING_16,
    },
    [HM_UART2_IDX] = {
        .huart.Instance = USART2,
        .huart.Init.BaudRate     = 9600,
        .huart.Init.WordLength   = UART_WORDLENGTH_8B,
        .huart.Init.StopBits     = UART_STOPBITS_1,
        .huart.Init.Parity       = UART_PARITY_NONE,
        .huart.Init.HwFlowCtl    = UART_HWCONTROL_NONE,
        .huart.Init.Mode         = UART_MODE_TX_RX,
        .huart.Init.OverSampling = UART_OVERSAMPLING_16,
    }
};

/**
 * @brief UART MSP Initialization 
 *        This function configures the hardware resources used in this example: 
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration  
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspInit(UART_HandleTypeDef *huart)
{  
    GPIO_InitTypeDef  GPIO_InitStruct;

    /* 1. Enable peripherals and GPIO Clocks */
    if (huart->Instance == USART1)
    {
        /* Enable GPIO TX/RX clock */
        __HAL_RCC_GPIOA_CLK_ENABLE();
        /* Enable USART1 clock */
        __HAL_RCC_USART1_CLK_ENABLE();
        
        /* 2. Configure peripheral GPIO */  
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin       = GPIO_PIN_9;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_NOPULL;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        GPIO_InitStruct.Pin = GPIO_PIN_10;
        HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    }
    else if (huart->Instance == USART2)
    {
        /* Enable GPIO TX/RX clock */
        __HAL_RCC_GPIOD_CLK_ENABLE();
        /* Enable USART1 clock */
        __HAL_RCC_USART2_CLK_ENABLE();
        
        /* 2. Configure peripheral GPIO */  
        /* UART TX GPIO pin configuration  */
        GPIO_InitStruct.Pin       = GPIO_PIN_5;
        GPIO_InitStruct.Alternate = GPIO_AF7_USART2;
        GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
        GPIO_InitStruct.Pull      = GPIO_NOPULL;
        GPIO_InitStruct.Speed     = GPIO_SPEED_FAST;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

        /* UART RX GPIO pin configuration  */
        GPIO_InitStruct.Pin = GPIO_PIN_6;
        HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
    }
}

/**
 * @brief UART MSP De-Initialization 
 *        This function frees the hardware resources used in this example:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO configuration to their default state
 * @param huart: UART handle pointer
 * @retval None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef *huart)
{
    /* 1. Reset peripherals */
    if (huart->Instance == USART1)
    {
        __HAL_RCC_USART1_FORCE_RESET();
        __HAL_RCC_USART1_RELEASE_RESET();
        
        /* 2. Disable peripherals and GPIO Clocks */
        /* Configure UART Tx as alternate function */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9);
        /* Configure UART Rx as alternate function */
        HAL_GPIO_DeInit(GPIOA, GPIO_PIN_10);
    }
    else if (huart->Instance == USART2)
    {
        __HAL_RCC_USART2_FORCE_RESET();
        __HAL_RCC_USART2_RELEASE_RESET();
        
        /* 2. Disable peripherals and GPIO Clocks */
        /* Configure UART Tx as alternate function */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_9);
        /* Configure UART Rx as alternate function */
        HAL_GPIO_DeInit(GPIOD, GPIO_PIN_10);
    }
}

uint32_t hm_uart_init(hm_uart_idx_t id)
{
    uint32_t ret = 0;
    
    if (id < NUM_OF_UARTS)
    {
        ret = HAL_UART_Init(&uart_drv[id].huart);
    }

    return ret;
}

uint32_t hm_uart_status(hm_uart_idx_t id)
{
    return HAL_UART_GetState(&uart_drv[id].huart);
}

uint32_t hm_uart_send(hm_uart_idx_t id, uint8_t *buf, uint32_t len, uint32_t timeout)
{
    uint32_t ret = 0;

    if (id < NUM_OF_UARTS)
    {
        ret = HAL_UART_Transmit(&uart_drv[id].huart, buf, len, timeout);
    }

    return ret;
}

uint32_t hm_uart_recv(hm_uart_idx_t id, uint8_t *buf, uint32_t len, uint32_t timeout)
{
    uint32_t ret = 0;

    if (id < NUM_OF_UARTS)
    {
        ret = HAL_UART_Receive(&uart_drv[id].huart, buf, len, timeout);
    }

    return ret;
}
