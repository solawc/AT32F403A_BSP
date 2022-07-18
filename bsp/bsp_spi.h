#ifndef __BSP_SPI_H
#define __BSP_SPI_H

#include "main.h"

#define FLASH_SPI_PORT_CLOCK()          crm_periph_clock_enable(CRM_GPIOB_PERIPH_CLOCK,TRUE)
#define FLASH_SPI_CLOCK()               crm_periph_clock_enable(CRM_SPI2_PERIPH_CLOCK,TRUE)
#define FLASH_SPI                       SPI2
#define FLASH_SPI_CS_PIN                GPIO_PINS_12
#define FLASH_SPI_CS_PORT               GPIOB
#define FLASH_SPI_CLK_PIN               GPIO_PINS_13
#define FLASH_SPI_CLK_PORT              GPIOB
#define FLASH_SPI_MISO_PIN              GPIO_PINS_14
#define FLASH_SPI_MISO_PORT             GPIOB
#define FLASH_SPI_MOSI_PIN              GPIO_PINS_15
#define FLASH_SPI_MOSI_PORT             GPIOB

#define SPI_CS_HIGH()                   gpio_bits_set(FLASH_SPI_CS_PORT,FLASH_SPI_CS_PIN) 
#define SPI_CS_LOW()                    gpio_bits_reset(FLASH_SPI_CS_PORT,FLASH_SPI_CS_PIN)   


void bsp_spi_init(void);
uint8_t bsp_spi_senddata(uint8_t data);
uint16_t bsp_spi_readdata(void);


#endif /* __BSP_SPI_H */