#include "gpio.h"


void Button_GPIOA_Init(){
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	GPIOA->MODER &=~GPIO_MODER_MODER0;
	GPIOA->PUPDR|=GPIO_PUPDR_PUPDR0_1;
	SYSCFG->EXTICR[1]&=~(0x0F<<0); //external interrupt configuration register 1

	EXTI->IMR|= EXTI_IMR_IM0; // Interrupt mask register - turn off mask for interrupts
	EXTI->EMR|= EXTI_EMR_EM0; // Event mask register

	EXTI->RTSR|= EXTI_RTSR_RT0; // RTSR - rising trigger selection register(front front)

	NVIC_SetPriority(EXTI0_1_IRQn, 1); // setting the priority
	//самый высокий приоритет, чтобы по нажатию кнопки выключить и включить считывание пространства
	NVIC_EnableIRQ(EXTI0_1_IRQn);//Enabling an interrupt in the interrupt controller
}

void EXTI0_1_IRQHandler(){
	EXTI->PR |= EXTI_PR_PIF0;
	TIM6->CR1 |= TIM_CR1_CEN;
}
