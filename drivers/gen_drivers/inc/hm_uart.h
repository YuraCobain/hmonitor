#ifndef __HM_UART__
#define __HM_UART__

typedef enum {                                       
    HM_UART1_IDX,
    HM_UART2_IDX,
    NUM_OF_UARTS
} hm_uart_idx_t;                                        

uint32_t hm_uart_init(hm_uart_idx_t id); 
uint32_t hm_uart_status(hm_uart_idx_t id); 
uint32_t hm_uart_send(hm_uart_idx_t id, uint8_t *buf, uint32_t len, uint32_t timeout);
uint32_t hm_uart_recv(hm_uart_idx_t id, uint8_t *buf, uint32_t len, uint32_t timeout);

#endif /* __HM_UART__ */     
