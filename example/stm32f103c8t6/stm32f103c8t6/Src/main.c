

#include "stm32.h"

#include "../LitoOS/include/LitoOS.h"
#include "../LitoOS/include/task.h"
#include "../LitoOS/include/semaphore_mutex.h"

#include <string.h>

extern UART_HandleTypeDef huart1;
LT_mutex_t lock;


void task1(const void* parameter)
{
	char* buff = "task1\r\n";

	while(1){
		HAL_UART_Transmit(&huart1,(uint8_t*)buff,strlen((char*)buff),HAL_MAX_DELAY);
		HAL_Delay(100);
	}
}


void task2(const void* parameter)
{
	char* buff = "task2\r\n";

	while(1){
		HAL_UART_Transmit(&huart1,(uint8_t*)buff,strlen((char*)buff),HAL_MAX_DELAY);
		HAL_Delay(1000);
	}
}

int main()
{
	Lito_task_t task;
	uint32_t parameter = 20;
	hardware_init();

	Lito_init();

	task.pid = 1;
	task.flag = 0;
	task.function = (void*)task1;
	task.stack_size = 0x200;
	task.parameter = &parameter;
	LT_task_create(&task);

	task.pid = 2;
	task.function = (void*)task2;
	task.stack_size = 0x200;
	task.parameter = NULL;
	LT_task_create(&task);

	LT_mutex_init(&lock,LT_MUTEX_UNLOCKED);

	Lito_start();

	while(1)
	{

	}
}
