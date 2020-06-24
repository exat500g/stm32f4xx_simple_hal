#include "iwdg.h"
#include "stm32f4xx.h"


void iwdg_init(void){
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	/* IWDG counter clock: LSI/32 */
	IWDG_SetPrescaler(IWDG_Prescaler_256);	//6.4ms/load
	IWDG_SetReload(469);	//469*6.4ms=3s
	/* Reload IWDG counter */
	IWDG_ReloadCounter();
	/* Enable IWDG (the LSI oscillator will be enabled by hardware) */
	IWDG_Enable();
}

void iwdg_reload(void){
    IWDG_ReloadCounter();
}

