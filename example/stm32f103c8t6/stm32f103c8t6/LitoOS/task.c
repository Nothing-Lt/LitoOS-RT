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

#include "../Inc/stm32.h"

pid_t pid;

LT_TCB_list_t* ready_queue;
LT_TCB_item_t* tcb_item_running_task;

TCB_t* tcb_save;
TCB_t* tcb_load;

LT_error_code_t LT_ready_queue_init()
{
    ready_queue = LT_list_create();
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

	// This is the very first task in this system,
	// in my design, the dummy thread will be this task.
	if(0 == ready_queue->length){
		tcb_item_running_task = tcb_item;
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
    tcb->priority = 0;
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
	LT_tcb_item_running_task_update();
	hardware_context_switch();
}

LT_TCB_item_t* LT_tcb_item_running_task_update()
{
	LT_TCB_item_t* updated_tcb_item = NULL;

	updated_tcb_item = tcb_item_running_task;

	if(NULL == tcb_item_running_task->next){
		tcb_save = &(((Lito_TCB_t*)(tcb_item_running_task->content))->tcb);
		tcb_load = &(((Lito_TCB_t*)(ready_queue->head->content))->tcb);
		tcb_item_running_task = ready_queue->head;
	}
	else{
		tcb_save = &(((Lito_TCB_t*)(tcb_item_running_task->content))->tcb);
		tcb_load = &(((Lito_TCB_t*)(tcb_item_running_task->next->content))->tcb);
		tcb_item_running_task = tcb_item_running_task->next;
	}

	return updated_tcb_item;
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


