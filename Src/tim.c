#include "tim.h"


extern long weight;
extern long memory_weight;


// настройка таймера для исключения дребезга
void TIM6_init()
{
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	TIM6->CR1 |= TIM_CR1_OPM; //one pulse mode
	TIM6->PSC = 800-1;
	TIM6->ARR = 10-1;

	TIM6->DIER |= TIM_DIER_UIE;
	NVIC_SetPriority(TIM6_DAC_IRQn, 3);
	NVIC_EnableIRQ(TIM6_DAC_IRQn);
}

void TIM6_DAC_IRQHandler(){
	TIM6->SR &= ~TIM_SR_UIF;
	button=Button_On;
	if(weight!=0){
		memory_weight=weight; // вес, который последний раз был измерен записываем в память
	}
	//отправить на дисплей 0!!!!!
	TIM6->CR1 &= ~TIM_CR1_CEN;
}
