#include "uart.h"


void uart_init(uart_t *u){
	u->rcc_init(u->uart_rcc,ENABLE);
	gpio_init_af(&u->tx);
	gpio_init_af(&u->rx);
	uint8_t ptx=0,prx=0;
	for(int i=0;i<16;i++){
		if(u->tx.pin==(1<<i)){
			ptx=i;
		}
		if(u->rx.pin==(1<<i)){
			prx=i;
		}
	}
	GPIO_PinAFConfig(u->tx.base,ptx,u->af);
    GPIO_PinAFConfig(u->rx.base,prx,u->af);
	NVIC_Init(&u->nvic);
}

void uart_configure(uart_t *u,USART_InitTypeDef *config){
	USART_Cmd(u->uart_base,DISABLE);
	USART_Init(u->uart_base,config);
	USART_Cmd(u->uart_base,ENABLE);
}

void uart_setISR(uart_t *u,uint16_t it,FunctionalState enable){
	USART_ITConfig(u->uart_base, it, enable);
}
void uart_clearFlag(uart_t *u,uint16_t flag){
	USART_ClearFlag(u->uart_base,flag);
}

void uart_putc(uart_t *u,uint8_t c){
	USART_TypeDef* uart=u->uart_base;
	while(!(uart->SR & USART_SR_TXE)){__ASM("nop");}
	uart->DR = c;
}

uint8_t uart_getc(uart_t *u){
	USART_TypeDef* uart=u->uart_base;
	while(uart->SR & USART_SR_RXNE){__ASM("nop");}
	return uart->DR;
}

bool uart_tryPutc(uart_t *u,uint8_t c){
    USART_TypeDef* uart=u->uart_base;
	if(uart->SR & USART_SR_TXE){
		uart->DR=c;
        return true;
	}
    return false;
}

bool uart_tryGetc(uart_t *u,uint8_t *c){
    USART_TypeDef* uart=u->uart_base;
	if(uart->SR & USART_SR_RXNE){
        if(c){
            *c=uart->DR;
        }
        return true;
	}
    return false;
}


