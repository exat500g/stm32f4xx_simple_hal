#pragma once

#include "stm32f4xx.h"
#include <stdbool.h>


#ifdef __cplusplus
extern "C"{
#endif

#define DIR_OUTPUT true
#define DIR_INPUT false
#define LOGIC_NORMAL false
#define LOGIC_INVERTED true
#define DEFAULT_SET true
#define DEFAULT_RESET false

typedef struct{
	GPIO_TypeDef *base;         //GPIOx
	uint16_t      pin;          //GPIO_Pin_x  //使用Pin而不是Bit的原因是gpio_set时效率高
    bool          direction;    //true:Output , false:input
    bool          inverted;     //false:high=true,low=false      true:high=false,low=true
	bool          initState;    //default value
}gpio_t;

void gpio_rcc_init(void);
void gpio_init(gpio_t *gpio); //push-pull output / float-input
void gpio_init2(gpio_t *gpio,GPIOOType_TypeDef otype,GPIOPuPd_TypeDef pupd);
void gpio_init_af(gpio_t *gpio);
void gpio_construct(gpio_t *port,GPIO_TypeDef* gpio,uint16_t pin,bool direction,bool inverted,bool initState);

__STATIC_INLINE void gpio_set(gpio_t *gpio,bool state){
	if(state^gpio->inverted){
		gpio->base->BSRRL|=gpio->pin;
	}else{
		gpio->base->BSRRH|=gpio->pin;
	}
}


__STATIC_INLINE bool gpio_get(gpio_t *gpio){
	return gpio->inverted^(((gpio->base->IDR)&(gpio->pin))?true:false);
}

__STATIC_INLINE bool gpio_getOutput(gpio_t *gpio){
	return gpio->inverted^(((gpio->base->ODR)&(gpio->pin))?true:false);
}

#ifdef __cplusplus
}
#endif

