#pragma once

#include <stdbool.h>
#include "stm32f4xx.h"

/*If the APB prescaler (PPRE1, PPRE2 in the RCC_CFGR register) is configured to a 
division factor of 1, TIMxCLK = PCLKx. Otherwise, the timer clock frequencies are set to 
twice to the frequency of the APB domainto which the timers are connected:
TIMxCLK = 2xPCLKx.*/
/* TIM1 = APB2*2 = (PCLK/2)*2 = PCLK
 * TIM8,9,10,11 = up
 * TIM other = APB1 = (PCLK/4)*2 = PCLK/2
 */

typedef struct{
	int id;
	TIM_TypeDef *base;
	void (*rcc_init)(uint32_t rcc, FunctionalState NewState);
	uint32_t rcc;
	TIM_TimeBaseInitTypeDef conf;
	NVIC_InitTypeDef nvic;
}tim_base_t;

//ARRʹ��,���иĶ�����������Ч
//��ʼ����ʱ��Ϊֹͣ״̬,��ҪsetEnable
void tim_init(tim_base_t *p);
void tim_setEnable(tim_base_t *p,FunctionalState enable);
void tim_setARRPreload(tim_base_t *p,bool enable);
void tim_setITUpdate(tim_base_t *p,FunctionalState enable);

//����clk��Ƶ
__STATIC_INLINE void tim_setPrescale(tim_base_t *p,uint16_t prescale){
	p->base->PSC=prescale;
}
//���ü���������ֵ
__STATIC_INLINE void tim_setReload(tim_base_t *p,uint16_t period){
	p->base->ARR=period;
}


