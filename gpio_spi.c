#include "gpio_spi.h"

static inline void read_bit_msb(gpio_t* gpio,uint8_t *data){
    data[0]<<=1;
    if(gpio_get(gpio)){
        data[0]|=0x01;
    }else{
        __nop();
        __nop();
        //data[0]|=0x00;
    }
}

uint8_t gpio_spi_read (gpio_spi_t* spi){
    uint8_t data=0;
    if(spi->clk && spi->miso){
        bool cpol=spi->cpol;
        bool cpha=spi->cpha;
        for(int i=0;i<8;i++){
            gpio_set(spi->clk,cpol);
            __nop();__nop();__nop();
            gpio_set(spi->clk,!cpol);
            __nop();__nop();__nop();
            if(!cpha){
                read_bit_msb(spi->miso,&data);
            }
            gpio_set(spi->clk,cpol);
            __nop();__nop();__nop();
            if(cpha){
                read_bit_msb(spi->miso,&data);
            }
/*            data<<=1;
            if(gpio_get(spi->miso)){
                data|=0x01;
            }else{
                data|=0x00;
            }
            gpio_set(spi->clk,true);
            __nop();__nop();__nop();*/
        }
    }
    return data;
}

static inline void write_bit_msb(gpio_t* gpio,uint8_t *data){
    if(data[0]&0x80){
        gpio_set(gpio,true);
    }else{
        gpio_set(gpio,false);
    }
    data[0]<<=1;
}

void    gpio_spi_write(gpio_spi_t* spi,uint8_t data){
    if(spi->clk && spi->mosi){
        bool cpol=spi->cpol;
        bool cpha=spi->cpha;
        for(int i=0;i<8;i++){
            gpio_set(spi->clk,cpol);
            __nop();__nop();__nop();
            gpio_set(spi->clk,!cpol);
            __nop();__nop();__nop();
            if(!cpha){
                write_bit_msb(spi->mosi,&data);
            }
            gpio_set(spi->clk,cpol);
            __nop();__nop();__nop();
            if(cpha){
                write_bit_msb(spi->mosi,&data);
            }
        }
    }
}
uint8_t gpio_spi_swap (gpio_spi_t* spi,uint8_t data){
    uint8_t rxData=0;
    if(spi->clk && spi->mosi && spi->miso){
        bool cpol=spi->cpol;
        bool cpha=spi->cpha;
        for(int i=0;i<8;i++){
            gpio_set(spi->clk,cpol);
            __nop();__nop();__nop();
            gpio_set(spi->clk,!cpol);
            __nop();__nop();__nop();
            if(!cpha){
                write_bit_msb(spi->mosi,&data);
                read_bit_msb(spi->miso,&rxData);
            }
            gpio_set(spi->clk,cpol);
            __nop();__nop();__nop();
            if(cpha){
                write_bit_msb(spi->mosi,&data);
                read_bit_msb(spi->miso,&rxData);
            }
        }
    }
    return rxData;
}
