#pragma once

#include "stm32f4xx.h"
#include "gpio.h"

typedef struct{
    gpio_t* clk;
    gpio_t* mosi;
    gpio_t* miso;
    bool cpol;
    bool cpha;
}gpio_spi_t;

uint8_t gpio_spi_read (gpio_spi_t*);
void    gpio_spi_write(gpio_spi_t*,uint8_t data);
uint8_t gpio_spi_swap (gpio_spi_t*,uint8_t data);
