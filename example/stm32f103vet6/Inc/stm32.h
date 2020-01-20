/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_H
#define __STM32_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

typedef struct {
	uint32_t r4,r5,r6,r7,r8,r9,r10,r11;
	uint32_t r0,r1,r2,r3,r12,lr,pc,xPSR;
}CONTENT_t;

typedef struct{
	CONTENT_t* stack_pointer;
}TCB_t;

typedef void function(const void*);

void hardware_init();

uint32_t hardware_tick_get();

void Error_Handler(void);

void hardware_context_switch();

void hardware_TCB_init(TCB_t* tcb,function* func,void* parameter,void* stack_pointer,size_t stack_size);

void LT_IRQ_enable();

void LT_IRQ_disable();

void LT_dummy_task(const void* arg);

void LT_first_task_start();

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
