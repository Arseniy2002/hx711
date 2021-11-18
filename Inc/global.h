#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "stm32f0xx.h"

extern uint8_t button;


extern long weight;
extern long weight_grams;
extern long array_weight[45];
extern long offset;
extern long memory_weight;


#define Button_On 1
#define Button_Off 0


#define SCK_HIGH() GPIOB->ODR|=GPIO_ODR_8
#define SCK_LOW() GPIOB->ODR&=~GPIO_ODR_8




#endif /* GLOBAL_H_ */
