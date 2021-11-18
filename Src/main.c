#include "main.h"

long weight=0;
long weight_grams=0;
long offset=0;
long array_weight[45];
long memory_weight=0;

uint8_t button=0;

void clock48Mhz_init() {
	RCC->CR &= ~RCC_CR_PLLON;
	while(RCC->CR & RCC_CR_PLLRDY);

	RCC->CFGR |= RCC_CFGR_PLLMUL12;

	RCC->CR |= RCC_CR_PLLON;
	while((RCC->CR & RCC_CR_PLLRDY) != RCC_CR_PLLRDY);

	RCC->CFGR |= RCC_CFGR_SW_1;	//as PLL

	SystemCoreClockUpdate();
}


int main(void){
	SYSCFG_Clock();
	clock48Mhz_init();
	HX711_init();
	while(1){
		HX711_get_data();
	}
}




