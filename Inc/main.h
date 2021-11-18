#ifndef MAIN_H_
#define MAIN_H_

#include <stdint.h>
#include "stm32f0xx.h"
#include "gpio.h"
#include "HX711.h"

#define SYSCFG_Clock() RCC->APB2ENR|=RCC_APB2ENR_SYSCFGEN

#endif /* MAIN_H_ */
