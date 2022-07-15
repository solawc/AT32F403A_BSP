#include "bsp_uart.h"

UART_TypeDef_t      my_uart;

void bsp_uart_nvic_init(void){
    nvic_priority_group_config(NVIC_PRIORITY_GROUP_3);
    nvic_irq_enable(DEBUG_UART_IRQ, 0, 0);
}

void bsp_uart_gpio_init(void){

    gpio_init_type GPIO_InitStruct = {0};

    DEBUG_UART_PORT_ENABLE();

    GPIO_InitStruct.gpio_mode = GPIO_MODE_MUX;
    GPIO_InitStruct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL; 
    GPIO_InitStruct.gpio_pull = GPIO_PULL_NONE; 
    GPIO_InitStruct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    GPIO_InitStruct.gpio_pins = DEBUG_UART_RX_PIN;
    gpio_init(DEBUG_UART_GPIO,&GPIO_InitStruct);

    GPIO_InitStruct.gpio_pins = DEBUG_UART_TX_PIN;
    gpio_init(DEBUG_UART_GPIO,&GPIO_InitStruct);
}

void bsp_uart_init(void){

    bsp_uart_gpio_init();
    bsp_uart_nvic_init();

    DEBUG_UART_CLOCK_ENABLE();
    usart_init(DEBUG_UART,DEBUG_UART_BAUDRATE,USART_DATA_8BITS,USART_STOP_1_BIT);
    usart_transmitter_enable(DEBUG_UART, TRUE);
    usart_receiver_enable(DEBUG_UART, TRUE);
    usart_enable(DEBUG_UART, TRUE);
    usart_interrupt_enable(DEBUG_UART,USART_RDBF_INT,TRUE);
}

/* 用对象的方式来编写，不管移植、还是复用多路串口，少写很多代码 */
/* Example */
bool my_bsp_uart_init(UART_TypeDef_t *uart) {

    DEBUG_UART_CLOCK_ENABLE();
    bsp_uart_gpio_init();
    bsp_uart_nvic_init();

    usart_init( uart->Instance,
                uart->baud,
                uart->Init->data_bit,
                uart->Init->stop_bit
            );
    switch(uart->Init->mode)
    {
        case UART_MODE_TX_ONLY: 
            usart_transmitter_enable(uart->Instance, TRUE);
        break;

        case UART_MODE_RX_ONLY: 
            usart_receiver_enable(uart->Instance, TRUE);
        break;

        case UART_MODE_TX_RX: 
            usart_transmitter_enable(uart->Instance, TRUE);
            usart_receiver_enable(uart->Instance, TRUE);
        break;

        default:
            return false;
    }
    
    usart_enable(uart->Instance, TRUE);

    return true;
}

/*
 * C标准库的重定向, 该方法适用于使用Keil/IAR等这类型的编译器，如果使用GCC/G++等编译链工具进行编译，
 * 请使用_write(int fd, char *ptr, int len)	
 * 进行重定向，否则会出现串口无法打印的情况
*/
#ifdef __CC_ARM
int fputc(int ch, FILE *f)
{   
    __IO uint16_t count = 4096;
	usart_data_transmit(DEBUG_UART,(uint16_t)ch);
    while(usart_flag_get(DEBUG_UART,USART_TDC_FLAG) == RESET && count != 0) {
        count--;
    }
	return (ch);
}
#else
int _write(int fd, char *ptr, int len)
{	
	HAL_UART_Transmit(&laser_uart, (uint8_t *)ptr, len, 1000);        //huart3是串口的句柄
	return len;
}
#endif


void DEBUG_UART_IRQHandler(){
    uint16_t data;

    if(usart_flag_get(DEBUG_UART,USART_RDBF_FLAG) == SET)
    {
        usart_flag_clear(DEBUG_UART,USART_RDBF_FLAG);
        data = usart_data_receive(DEBUG_UART);
        usart_data_transmit(DEBUG_UART,data);
    }
}

