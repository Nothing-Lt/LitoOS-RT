#include "gd32vf103.h"

#include "LitoOS/include/LitoOS.h"
#include "LitoOS/include/task.h"
#include "LitoOS/include/timer.h"
#include "LitoOS/include/semaphore_mutex.h"

#include "RISCV/longan_nano.h"
#include "lcd.h"

LT_semaphore_t* semaphore1;

void task2(const void* parameter)
{
	int i;
    char buff[50];

    if(LT_ERR_OK != LT_timer_event_regist(NULL, hardware_tick_get() + 40, NULL, semaphore1, LT_TIMER_EVENT_SEMAPHORE)){
        while(1){}
    }

	for(i=0;;){
        LT_semaphore_get(semaphore1,LT_QUEUE_FLAG_FROM_TASK);
        sprintf(buff,"%u",hardware_tick_get());
        LCD_ShowString(0,0,buff,BLACK);
        if(i>128){
			i=0;
		}

        if(LT_ERR_OK != LT_timer_event_regist(NULL, hardware_tick_get() + 10, NULL, semaphore1, LT_TIMER_EVENT_SEMAPHORE)){
            while(1){}
        }
	}
}

void task3(const void* parameter)
{
	int i;
    char buff[50];

	while(1){
        sprintf(buff,"%u",hardware_tick_get());
        LCD_ShowString(0,30,buff,BLACK);
	}
}

int main()
{
	Lito_task_t task;

    LT_IRQ_disable();
       
    hardware_init();

    Lito_init();
    
	task.flag = 0;
	task.function = (void*)task2;
	task.parameter = NULL;
	task.pid = 2;
    task.priority = 0;
	task.stack_size = 1024;
    LT_task_create(&task);

	task.function = (void*)task3;
	task.pid = 3;
    task.priority = 1;
	task.stack_size = 1024;
    LT_task_create(&task);

    semaphore1 = LT_semaphore_create(5);
    
    Lito_start();

    return 0;
}