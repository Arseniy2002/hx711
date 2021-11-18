#ifndef GPIO_H_
#define GPIO_H_


#include "global.h"
#include "stm32f0xx.h"

/**************************** FOR TFT DISPLAY
 * PA4 - CS
 * PA2 - RESET
 * PA3 - DC (data command)
 * PA7 - MOSI
 * PA5 - SCK
 * PA6 - MISO
 * PA1 - LED
 * ***************************************
 * for HX711
 *
 * PB0 - SCK
 * PB1 - DOUT
 *
 * **/

void Button_GPIOA_Init();
void EXTI0_1_IRQHandler();

#endif /* GPIO_H_ */
