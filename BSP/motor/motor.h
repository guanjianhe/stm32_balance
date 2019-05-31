#ifndef MOTOR_H
#define MOTOR_H

#include "stm32f10x.h"

extern void motor_init(void);

#define PWMA TIM2->CCR3
#define PWMB TIM2->CCR4

#define AIN1_H  GPIOB->BSRR = GPIO_Pin_14
#define AIN1_L  GPIOB->BRR = GPIO_Pin_14

#define AIN2_H  GPIOB->BSRR = GPIO_Pin_15
#define AIN2_L  GPIOB->BRR = GPIO_Pin_15

#define BIN1_H  GPIOB->BSRR = GPIO_Pin_13
#define BIN1_L  GPIOB->BRR = GPIO_Pin_13

#define BIN2_H  GPIOB->BSRR = GPIO_Pin_12
#define BIN2_L  GPIOB->BRR = GPIO_Pin_12




#endif
