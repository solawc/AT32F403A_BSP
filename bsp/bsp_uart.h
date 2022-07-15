#ifndef __BSP_UART_H
#define __BSP_UART_H

#include "main.h"

#define DEBUG_UART_CLOCK_ENABLE()           crm_periph_clock_enable(CRM_USART3_PERIPH_CLOCK,TRUE)
#define DEBUG_UART_PORT_ENABLE()            crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK,TRUE)

#define DEBUG_UART                          USART3
#define DEBUG_UART_IRQ                      USART3_IRQn
#define DEBUG_UART_IRQHandler               USART3_IRQHandler
#define DEBUG_UART_GPIO                     GPIOB
#define DEBUG_UART_TX_PIN                   GPIO_PINS_10
#define DEBUG_UART_RX_PIN                   GPIO_PINS_11
#define DEBUG_UART_BAUDRATE                 115200

/* 用于开启/关闭调试模式 */
#define DEBUG_MODE
#ifdef DEBUG_MODE
#define DEBUG_ERROR(fmt,arg...)             do{printf("<<-ERROR->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)
#define DEBUG_PRINT(fmt,arg...)             do{printf("<<-DEBUG->> [%d]"fmt"\r\n",__LINE__, ##arg);}while(0)   
#define DEBUG_PRINTF(fmt, arg...)           do{printf(fmt, ##arg);}while(0)  
#else
#define DEBUG_ERROR(fmt,arg...)       
#define DEBUG_PRINT(fmt,arg...)       
#define DEBUG_PRINTF(fmt, arg...)     
#endif

typedef enum {
    UART_MODE_TX_ONLY,
    UART_MODE_RX_ONLY,
    UART_MODE_TX_RX,
}UART_trans_mode_t;


typedef struct {
    usart_data_bit_num_type             data_bit;
    usart_stop_bit_num_type             stop_bit;
    usart_hardware_flow_control_type    hw_ctrl;
    UART_trans_mode_t                   mode;
}UART_InitDef;

typedef struct {
    usart_type                  *Instance;
    UART_InitDef                *Init;
    uint32_t                    baud;
}UART_TypeDef_t;



void bsp_uart_init(void);


#endif /* __BSP_UART__H */

