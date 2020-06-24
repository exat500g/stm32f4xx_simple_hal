#pragma once

#include "stm32f4xx.h"
#include "gpio.h"

typedef struct{
	USART_TypeDef *uart_base;
	void (*rcc_init)(uint32_t RCC_APB1Periph, FunctionalState NewState);
	uint32_t uart_rcc;
	gpio_t tx;
	gpio_t rx;
	uint8_t af;
	NVIC_InitTypeDef nvic;
}uart_t;

//外设时钟和端口初始化
void uart_init(uart_t *u);
//外设设置初始化
void uart_configure(uart_t *u,USART_InitTypeDef *config);
void uart_setISR(uart_t *u,uint16_t it,FunctionalState enable);
void uart_clearFlag(uart_t *u,uint16_t flag);

//block IO
void    uart_putc(uart_t *u,uint8_t c);
uint8_t uart_getc(uart_t *u);

//non-block IO
bool uart_tryPutc(uart_t *u,uint8_t c);
bool uart_tryGetc(uart_t *u,uint8_t *c);

