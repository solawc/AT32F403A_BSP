#include "main.h"

int main(void){

    uint32_t flash_id = 0;
    uint8_t Tx_Buffer[] = "hejiahui";
    uint8_t Rx_Buffer[50];
    system_clock_config();
    bsp_uart_init();
    bsp_spi_init();

    printf("hello world\n");
    flash_id = w25qxx_readID();
    printf("flash_id = 0x%x\n",flash_id);


    w25qxx_sectorerase(0x00);
    w25qxx_buffwrite(Tx_Buffer,0x00,8);
    w25qxx_readbuff(Rx_Buffer,0x00,8);
    printf("buffread = %s\n",Rx_Buffer);
    while(1){
		
		
		
    }
}

