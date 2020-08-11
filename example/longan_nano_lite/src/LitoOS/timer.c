/**
 * @file timer.c
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */


#include "include/timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "include/LitoOS.h"
#include "include/list.h"

#include "../RISCV/longan_nano.h"

LT_timer_event_list_t* timer_event_list;

LT_error_code_t LT_timer_event_init()
{
    timer_event_list = LT_list_create(NULL);
    if(NULL == timer_event_list){
        return LT_ERR_FAILED;
    }

    return LT_ERR_COMPLETE;
}

/**
 * This function will allocate the memory space for both timer_event_item and timer_event.
 * Since it calls malloc only once, so memory space is organized as follow:
 *    |-----------------|--------------------------------|
 *    |sizeof(list_item)|       sizeof(timer_event)      |
 *    |-----------------|--------------------------------|
 *    ^                 ^
 *    timer_event_item  timer_event
 */
LT_error_code_t LT_timer_event_regist(LT_timer_event_item_t** timer_event_handle,uint32_t issue_at, handler_func* handler, LT_semaphore_t* semaphore_queue,LT_TIMER_EVENT_FLAG flag)
{
    LT_timer_event_item_t* timer_event_item = NULL;
    LT_timer_event_t* timer_event = NULL;

    if((LT_TIMER_EVENT_FUNCTION == flag) && (NULL == handler)){
        return LT_ERR_PARAMETER;
    }

    if((LT_TIMER_EVENT_SEMAPHORE == flag) && (NULL == semaphore_queue)){
        return LT_ERR_PARAMETER;
    }

    if(hardware_tick_get() > issue_at){
        return LT_ERR_PARAMETER;
    }

    timer_event_item = (LT_timer_event_item_t*)malloc(sizeof(LT_timer_event_item_t) + sizeof(LT_timer_event_t));
    if(NULL == timer_event_item){
        return LT_ERR_FAILED;
    }

    timer_event = (LT_timer_event_t*)(((uint32_t)timer_event_item) + sizeof(LT_timer_event_item_t));
    timer_event->flag = flag;
    timer_event->issue_at = issue_at;
    if(LT_TIMER_EVENT_SEMAPHORE == flag){
        timer_event->semaphore_queue = semaphore_queue;
        timer_event->handler = NULL;
    }
    if(LT_TIMER_EVENT_FUNCTION == flag){
        timer_event->semaphore_queue = NULL;
        timer_event->handler = handler;
    }

    timer_event_item->content = (void*)timer_event;
    timer_event_item->next = timer_event_item->prev = NULL;

    if(NULL != timer_event_handle){
        *timer_event_handle = timer_event_item;
    }

    return LT_list_insert(timer_event_list,timer_event_item);
}

LT_error_code_t LT_timer_event_remove(LT_timer_event_item_t* timer_event_handle)
{
    if(NULL == timer_event_handle){
        return LT_ERR_PARAMETER;
    }

    return LT_list_remove(timer_event_list,timer_event_handle);
}
