#ifndef HX711_H_
#define HX711_H_

#include "stm32f0xx.h"
#include "stdlib.h"//for function itoa
#include "global.h"
#include "tim.h"

void HX711_init();
long HX711_Get_3byte();
void HX711_work_on();
void pulse(uint8_t time);
long HX711_read_average(uint8_t times);
long HX711_get_value(long data);
long get_units(uint8_t times);
void HX711_get_data();
void power_down();
void Calibration();
void Set_offset(long data);
void Set_scale(long scale);
long calibration_array();
void delay(uint32_t tick);
void GPIOB_init_HX711();

#endif /* HX711_H_ */
