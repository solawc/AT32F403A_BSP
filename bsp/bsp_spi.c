#include "bsp_spi.h"

void bsp_spi_gpio_init(void){

    gpio_init_type GPIO_InitStruct = {0};
    
    FLASH_SPI_PORT_CLOCK();

    GPIO_InitStruct.gpio_mode = GPIO_MODE_OUTPUT;
    GPIO_InitStruct.gpio_out_type = GPIO_OUTPUT_PUSH_PULL; 
    GPIO_InitStruct.gpio_pull = GPIO_PULL_UP; 
    GPIO_InitStruct.gpio_drive_strength = GPIO_DRIVE_STRENGTH_STRONGER;
    GPIO_InitStruct.gpio_pins = FLASH_SPI_CS_PIN;
    gpio_init(FLASH_SPI_CS_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.gpio_mode = GPIO_MODE_MUX;
    GPIO_InitStruct.gpio_pins = FLASH_SPI_CLK_PIN;
    gpio_init(FLASH_SPI_CLK_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.gpio_mode = GPIO_MODE_MUX;
    GPIO_InitStruct.gpio_pins = FLASH_SPI_MISO_PIN;
    gpio_init(FLASH_SPI_MISO_PORT,&GPIO_InitStruct);

    GPIO_InitStruct.gpio_mode = GPIO_MODE_MUX;
    GPIO_InitStruct.gpio_pins = FLASH_SPI_MOSI_PIN;
    gpio_init(FLASH_SPI_MOSI_PORT,&GPIO_InitStruct);

    SPI_CS_HIGH();

}

void bsp_spi_init(void){

    spi_init_type spi_init_struct;

    bsp_spi_gpio_init();
    FLASH_SPI_CLOCK();

    spi_default_para_init(&spi_init_struct);
    spi_init_struct.cs_mode_selection = SPI_CS_SOFTWARE_MODE;
    spi_init_struct.master_slave_mode = SPI_MODE_MASTER;
    spi_init_struct.transmission_mode = SPI_TRANSMIT_FULL_DUPLEX;
    spi_init_struct.clock_phase = SPI_CLOCK_PHASE_2EDGE;
    spi_init_struct.clock_polarity = SPI_CLOCK_POLARITY_HIGH;
    spi_init_struct.first_bit_transmission = SPI_FIRST_BIT_MSB;
    spi_init_struct.frame_bit_num = SPI_FRAME_8BIT;
    spi_init_struct.mclk_freq_division = SPI_MCLK_DIV_8;
    spi_init(FLASH_SPI,&spi_init_struct);

    spi_enable(FLASH_SPI,TRUE);

}

uint8_t bsp_spi_senddata(uint8_t data){

    uint8_t readdata;
    spi_i2s_data_transmit(FLASH_SPI,data);
    while(spi_i2s_flag_get(FLASH_SPI,SPI_I2S_RDBF_FLAG) == RESET){  

    } 
    readdata = spi_i2s_data_receive(FLASH_SPI);
    while(spi_i2s_flag_get(FLASH_SPI,SPI_I2S_BF_FLAG) != RESET){

    }
    return readdata;

}

uint16_t bsp_spi_readdata(void){

    return (bsp_spi_senddata(Dummy_Byte));

}


