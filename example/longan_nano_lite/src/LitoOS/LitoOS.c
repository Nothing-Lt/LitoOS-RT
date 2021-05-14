/*
 * LitoOS.c
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */
#include "include/LitoOS.h"

#include "include/task.h"
#include "include/timer.h"

#include "../RISCV/longan_nano.h"
#include "lcd.h"

extern volatile pid_t pid;
extern LT_list_item_t volatile * tcb_item_running_task;

LT_SCHEDULE_STATUS lt_schedule_status;

void Lito_init()
{
	Lito_task_t dummy_task;

	LT_IRQ_disable();

	dummy_task.flag = 0;
	dummy_task.function = &LT_dummy_task;
	dummy_task.parameter = NULL;
	dummy_task.pid = pid = 1;
	dummy_task.priority = 0xffffffff; // Lowest priority
	dummy_task.stack_size = 0x400;

	lt_schedule_status = LT_SCHEDULE_NOT_RUNNING;

	LT_timer_event_init();

	LT_ready_queue_init();

	LT_task_create(&dummy_task);
}

void Lito_start()
{
	lt_schedule_status = LT_SCHEDULE_RUNNING;

	LT_IRQ_enable();
	LT_tcb_item_running_task_update();

	LT_first_task_start();
}
