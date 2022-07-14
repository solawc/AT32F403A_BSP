#include "bsp_uart.h"

void bsp_uart_nvic_init(void){

    nvic_priority_group_config(NVIC_PRIORITY_GROUP_3);
    nvic_irq_enable(DEBUG_UART_IRQ,0,0);

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



int fputc(int ch, FILE *f)
{
	usart_data_transmit(DEBUG_UART,(uint16_t)ch);
    while(usart_flag_get(DEBUG_UART,USART_TDC_FLAG) == RESET)
    {

    }
	return (ch);
}



void DEBUG_UART_IRQHandler(){
    
    uint16_t data;

    if(usart_flag_get(DEBUG_UART,USART_RDBF_FLAG) == SET)
    {
        usart_flag_clear(DEBUG_UART,USART_RDBF_FLAG);
        data = usart_data_receive(DEBUG_UART);
        usart_data_transmit(DEBUG_UART,data);
    }

}


