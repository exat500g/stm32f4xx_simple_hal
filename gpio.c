#include "gpio.h"

void gpio_rcc_init(void){
	RCC_AHB1PeriphClockCmd(
	RCC_AHB1Periph_GPIOA|
	RCC_AHB1Periph_GPIOB|
	RCC_AHB1Periph_GPIOC|
	RCC_AHB1Periph_GPIOD|
	RCC_AHB1Periph_GPIOE|
	RCC_AHB1Periph_GPIOF|
	RCC_AHB1Periph_GPIOG|
	RCC_AHB1Periph_GPIOH|
	RCC_AHB1Periph_GPIOI|
	RCC_AHB1Periph_GPIOJ|
	RCC_AHB1Periph_GPIOK,
	ENABLE);
}

void gpio_init(gpio_t *gpio){
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = gpio->pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode  = gpio->direction?GPIO_Mode_OUT:GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(gpio->base, &GPIO_InitStructure);
	gpio_set(gpio,gpio->initState);
}

void gpio_init2(gpio_t *gpio,GPIOOType_TypeDef otype,GPIOPuPd_TypeDef pupd){
    GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = gpio->pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode  = gpio->direction?GPIO_Mode_OUT:GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = otype;
	GPIO_InitStructure.GPIO_PuPd  = pupd;
	GPIO_Init(gpio->base, &GPIO_InitStructure);
	gpio_set(gpio,gpio->initState);
}

void gpio_init_af(gpio_t *gpio){
    GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin   = gpio->pin;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
	GPIO_Init(gpio->base, &GPIO_InitStructure);
	gpio_set(gpio,gpio->initState);
}

void gpio_construct(gpio_t *gpio,GPIO_TypeDef* base,uint16_t pin,bool direction,bool inverted,bool initState){
    gpio->base=base;
    gpio->pin=pin;
    gpio->direction=direction;
    gpio->inverted=inverted;
    gpio->initState=initState;
    gpio_init(gpio);
}

