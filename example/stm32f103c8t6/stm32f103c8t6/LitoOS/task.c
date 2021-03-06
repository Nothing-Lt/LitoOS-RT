/*
 * task.c
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */
#include "include/task.h"

#include <stdlib.h>

#include "include/LitoOS.h"
#include "include/list.h"
#include "include/schedule.h"

#include "../Inc/stm32.h"

pid_t pid;

LT_TCB_list_t* ready_queue;
LT_TCB_item_t* tcb_item_running_task;

TCB_t* tcb_running;

LT_error_code_t LT_ready_queue_init()
{
    ready_queue = LT_list_create(&insert_OK);
    if(NULL == ready_queue){
    	return LT_ERR_FAILED;
    }

    return LT_ERR_COMPLETE;
}

LT_error_code_t LT_ready_queue_insert(LT_TCB_item_t* tcb_item)
{
	if(NULL == tcb_item){
		return LT_ERR_PARAMETER;
	}

	return LT_list_insert(ready_queue,tcb_item);
}

LT_error_code_t LT_ready_queue_remove(LT_TCB_item_t* tcb_item)
{
	if(NULL == tcb_item){
		return LT_ERR_PARAMETER;
	}

	return LT_list_remove(ready_queue,tcb_item);
}

/**
 * This function will allocate the memory space for tcb_item, tcb and stack for task.
 * Since it calls malloc only once, so memory space is organized as follow:
 *    |-----------------|-----------|--------------------|
 *    |sizeof(list_item)|sizeof(tcb)|   sizeof(stack)    |
 *    |-----------------|-----------|--------------------|
 *    ^                 ^           ^
 *    tcb_item          tcb         stack
 */
LT_TCB_item_t* LT_task_create(Lito_task_t* task)
{
	Lito_TCB_t* tcb = NULL;
	LT_TCB_item_t* tcb_item = NULL;

    if(NULL == task){
        return NULL;
    }

    // Allocate Lito_TCB block and stack space for this task.
    tcb_item = (LT_list_item_t*)malloc(sizeof(LT_TCB_item_t) + sizeof(Lito_TCB_t) + (task->stack_size));
    if(NULL == tcb_item){
        return NULL;
    }

    tcb = (Lito_TCB_t*)(((uint32_t)tcb_item) + sizeof(LT_TCB_item_t));

    hardware_TCB_init(&(tcb->tcb), task->function,
    				  task->parameter, (void*)(((uint32_t)tcb_item) + sizeof(LT_TCB_item_t) + sizeof(Lito_TCB_t)),
					  task->stack_size);

    tcb->pid = task->pid;
    tcb->status = RUNNING;
    tcb->priority = task->priority;
    tcb->function = task->function;
    tcb->stack_size = task->stack_size;

    tcb_item->content = tcb;
    tcb_item->next = tcb_item->prev = NULL;

    if(LT_ERR_COMPLETE != LT_ready_queue_insert(tcb_item)){
    	// This should not happen
    	while(1){

    	}
    }

    return tcb_item;
}


void LT_task_switch()
{
    hardware_context_switch();
}

void LT_tcb_item_running_task_update()
{
    tcb_item_running_task = ready_queue->head;
    tcb_running = &(((Lito_TCB_t*)(tcb_item_running_task->content))->tcb);
}

/**
 * Get my TCB pointer, so that I can use it for some purpose.
 * Parameter:
 *   void
 * Return value:
 * Address of my TCB.
 */
LT_TCB_item_t* LT_TCB_get()
{
    return tcb_item_running_task;
}


