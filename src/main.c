#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "hm_led.h"
#include "hm_msg_ch.h"

static void vTestTask(void *arg);
static void vSendTask1(void *arg);
static void vSendTask2(void *arg);
static void vRecvTask(void *arg);

static void SystemClock_Config(void);

/**
 * @brief  Main program
 * @param  None
 * @retval None
 */
int main(void)
{
    /* STM32F4xx HAL library initialization:
       - Configure the Flash prefetch, instruction and Data caches
       - Configure the Systick to generate an interrupt each 1 msec
       - Set NVIC Group Priority to 4
       - Global MSP (MCU Support Package) initialization
       */
    HAL_Init();  

    /* Configure LED3 and LED4 */
    hm_led_init(HM_LED1);
    hm_led_init(HM_LED2);

    /* Configure the system clock to 180 MHz */
    SystemClock_Config();

    /* Thread 1 definition */
    xTaskCreate(vTestTask, "test", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    xTaskCreate(vRecvTask, "recv_test", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    /* Start scheduler */
    vTaskStartScheduler();

    return 0;
}

/**
 * @brief  Toggle LED3 and LED4 thread
 * @param  thread not used
 * @retval None
 */
static void vTestTask(void *arg)
{
    (void) arg;

    while (1)
    {
        BSP_LED_Toggle(LED3);
        vTaskDelay(5000);

        BSP_LED_Toggle(LED4);
        vTaskDelay(5000);
    }
}

static void vSendTask1(void *arg)
{
    (void) arg;
    hm_msg_ch_t* ch = hm_msg_ch_attach("recv_task");

    while (1)    
    {
        static uint32_t count1 = 1000;
        
        BSP_LED_Toggle(LED3);
        vTaskDelay(500);
        hm_msg_ch_send(ch, &count1);
        count1++;
        BSP_LED_Toggle(LED4);
        vTaskDelay(500);
    }
}

static void vSendTask2(void *arg)
{
    (void) arg;
    hm_msg_ch_t* ch = hm_msg_ch_attach("recv_task");

    while (1)
    {
        static uint32_t count2 = 3000;
        
        BSP_LED_Toggle(LED3);
        vTaskDelay(200);
        hm_msg_ch_send(ch, &count2);
        count2++;
        BSP_LED_Toggle(LED4);
        vTaskDelay(200);
    }


}

static void vRecvTask(void *arg)
{
    (void) arg;

    msg_t msg;
    hm_msg_ch_t* ch = hm_msg_ch_init("recv_task", 4);

    xTaskCreate(vSendTask1, "send_test1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(vSendTask2, "send_test2", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

    while (1)
    {
        while (hm_msg_ch_recv(ch, &msg) == pdPASS)
        {
            (void) msg;
        }
        vTaskDelay(500);

    }
}
/**
 * @brief  System Clock Configuration
 *         The system Clock is configured as follow : 
 *            System Clock source            = PLL (HSE)
 *            SYSCLK(Hz)                     = 180000000
 *            HCLK(Hz)                       = 180000000
 *            AHB Prescaler                  = 1
 *            APB1 Prescaler                 = 4
 *            APB2 Prescaler                 = 2
 *            HSE Frequency(Hz)              = 8000000
 *            PLL_M                          = 8
 *            PLL_N                          = 360
 *            PLL_P                          = 2
 *            PLL_Q                          = 7
 *            VDD(V)                         = 3.3
 *            Main regulator output voltage  = Scale1 mode
 *            Flash Latency(WS)              = 5
 * @param  None
 * @retval None
 */
static void SystemClock_Config(void)
{
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;

    /* Enable Power Control clock */
    __HAL_RCC_PWR_CLK_ENABLE();

    /* The voltage scaling allows optimizing the power consumption when the device is 
       clocked below the maximum system frequency, to update the voltage scaling value 
       regarding system frequency refer to product datasheet.  */
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 360;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    /* Activate the Over-Drive mode */
    HAL_PWREx_EnableOverDrive();

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 
       clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;  
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;  
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
}

#ifdef  USE_FULL_ASSERT
/**
 * @brief  Reports the name of the source file and the source line number
 *   where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

    /* Infinite loop */
    while (1)
    {
    }
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
