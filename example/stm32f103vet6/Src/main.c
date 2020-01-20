/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "stm32.h"

#include <string.h>

#include "../LitoOS/include/LitoOS.h"
#include "../LitoOS/include/task.h"
#include "../LitoOS/include/semaphore_mutex.h"

UART_HandleTypeDef huart1;

void task1()
{
	uint8_t buff[10];

	sprintf((char*)buff,"task 1\r\n");

	while(1){
		HAL_UART_Transmit(&huart1,buff,strlen((char*)buff),HAL_MAX_DELAY);
		HAL_Delay(10);
	}
}

void task2(const void* parameter)
{
	uint8_t buff[10] = {0xff};

	sprintf((char*)buff,"task 2\r\n");

	while(1){
		HAL_UART_Transmit(&huart1,buff,strlen((char*)buff),HAL_MAX_DELAY);
		HAL_Delay(300);
	}
}

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
	Lito_task_t task;
	uint32_t parameter = 20;

	hardware_init();
	Lito_init();

	task.pid = 1;
	task.flag = 0;
	task.function = &task1;
	task.stack_size = 0x200;
	task.parameter = &parameter;
	LT_task_create(&task);

	task.pid = 3;
	task.function = &task2;
	task.stack_size = 0x200;
	task.parameter = NULL;
	LT_task_create(&task);

	Lito_start();

	while (1){
	}
  /* USER CODE END 3 */
}

