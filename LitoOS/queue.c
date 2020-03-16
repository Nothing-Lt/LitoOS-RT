/*
 * queue.c
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */
#include "include/queue.h"
#include "include/LitoOS.h"
#include "include/task.h"

#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

extern LT_TCB_list_t* ready_queue;

/**
 * Initialize a queue
 */
void LT_queue_init(LT_queue_t* queue,uint32_t queue_length,size_t ele_size,void* queue_buffer)
{
    if(NULL == queue){
        return;
    }

    if(0 == queue_length){
        return;
    }

    queue->ele_size     = ele_size;
    queue->ele_number   = 0;
    queue->queue_length = queue_length;
    queue->queue_buffer = queue_buffer;
    queue->read_from    = \
    queue->write_to     = queue_buffer;
#if 1 == PERFORMANCE_IS_MORE_IMPORTANT
    queue->tcb_pending_to_receive = LT_list_create(NULL);
    queue->tcb_pending_to_send    = LT_list_create(NULL);
#endif
}

LT_queue_t* LT_queue_create(uint32_t queue_length,size_t ele_size)
{
    void* queue_buffer = NULL;
    LT_queue_t* queue = NULL;

    if(0 == queue_length){
        return NULL;
    }

    queue = (LT_queue_t*)malloc(sizeof(LT_queue_t) + (queue_length * ele_size));
    if(NULL == queue){
        while(1);
    }

    // If ele_size is 0, this means no need any buffer for this queue
    if(0 == ele_size){
        queue_buffer = NULL;
    }
    else{
        queue_buffer = (void*) (((uint32_t)queue) + sizeof(LT_queue_t));
    }

    LT_queue_init(queue,queue_length,ele_size,queue_buffer);

    return queue;
}


#if 0 == PERFORMANCE_IS_MORE_IMPORTANT
/**
 *	These LT_queue_put and LT_queue_get function are defined for saving memory space,
 *	it will not set the task to be blocked,
 *	so this means it need developer himself to write the application in this way:
 *	while(LT_ERR_FULL == LT_queue_put(queue,item,LT_QUEUE_FLAG_FROM_TASK));
 *	and
 *	while(LT_ERR_EMPTY == LT_queue_get(queue,item,LT_QUEUE_FLAG_FROM_TASK));
 *	usage example two-task model:
 *
 *  void t1(void* arg)
 *  {
 *      unsigned i = 0;
 *
 *      while(1){
 *          while(LT_ERR_FULL == LT_queue_put(queue,&i,LT_QUEUE_FLAG_FROM_TASK)){
 *          	context_switch();
 *          }
 *          i++;
 *          sleep(2);
 *      }
 *
 *      return NULL;
 *  }
 *
 *  void t2(void* arg)
 *  {
 *      unsigned v = 0xFFFFFFFF;
 *
 *      while(1){
 *          while(LT_ERR_EMPTY == LT_queue_get(queue,&v,LT_QUEUE_FLAG_FROM_TASK)){
 *          	context_switch();
 *          }
 *          printf("%u\n",v);
 *          sleep(1);
 *      }
 *      return NULL;
 *  }
 */
LT_error_code_t LT_queue_put(LT_queue_t* queue,void* item,LT_QUEUE_FLAG flag)
{
    LT_error_code_t result = LT_ERR_FULL;

    // Empty queue
    if(NULL == queue){
        return LT_ERR_PARAMETER;
    }

    // this is not semaphore but item is empty
    if((!(LT_QUEUE_AS_SEMAPHORE & flag)) && (NULL == item)){
        return LT_ERR_PARAMETER;
    }

    // This is come from normal task not IRQ
    if(LT_QUEUE_FLAG_FROM_TASK & flag){
        LT_IRQ_disable();
    }

    if(queue->queue_length > queue->ele_number){
        if(!(LT_QUEUE_AS_SEMAPHORE & flag)){
            memcpy(queue->write_to,item,queue->ele_size);

            queue->write_to = (void*)(((uint32_t)(queue->write_to)) + queue->ele_size);
            if((uint32_t)queue->write_to >= ((uint32_t)(queue->queue_buffer) + (queue->queue_length * queue->ele_size))){
                queue->write_to = queue->queue_buffer;
            }
        }
         queue->ele_number += 1;

        result = LT_ERR_COMPLETE;
    }
    else{
        result = LT_ERR_FULL;
    }

    if(LT_QUEUE_FLAG_FROM_TASK & flag){
        LT_IRQ_enable();
    }

    return result;
}

LT_error_code_t LT_queue_get(LT_queue_t* queue,void* item,LT_QUEUE_FLAG flag)
{
    LT_error_code_t result = LT_ERR_EMPTY;

    // Empty queue
    if(NULL == queue){
        return LT_ERR_PARAMETER;
    }

    // this is not semaphore but item is empty
    if(!(LT_QUEUE_AS_SEMAPHORE & flag) && (NULL == item)){
        return LT_ERR_PARAMETER;
    }

    //LT_QUEUE_FLAG flag is come from normal task not IRQ
    if(LT_QUEUE_FLAG_FROM_TASK & flag){
        LT_IRQ_disable();
    }

    if(0 < queue->ele_number){
        if(!(LT_QUEUE_AS_SEMAPHORE & flag)){
            memcpy(item,queue->read_from,queue->ele_size);

            queue->read_from = (void*)(((uint32_t)(queue->read_from)) + queue->ele_size);
            if((uint32_t)queue->read_from >= ((uint32_t)(queue->queue_buffer) + (queue->queue_length * queue->ele_size))){
                queue->read_from = queue->queue_buffer;
            }
        }

        queue->ele_number -= 1;

        result = LT_ERR_COMPLETE;
    }
    else{
        result = LT_ERR_EMPTY;
    }

    if(LT_QUEUE_FLAG_FROM_TASK & flag){
        LT_IRQ_enable();
    }

    return result;
}
#elif 1 == PERFORMANCE_IS_MORE_IMPORTANT

LT_error_code_t LT_queue_put(LT_queue_t* queue,void* item,LT_QUEUE_FLAG flag)
{
    LT_TCB_item_t* current_tcb_item = NULL;
    LT_TCB_item_t* pending_tcb_item = NULL;
    LT_error_code_t result = LT_ERR_FULL;

    // Empty queue
    if(NULL == queue){
        return LT_ERR_PARAMETER;
    }

    // this is not semaphore but item is empty
    if((!(LT_QUEUE_AS_SEMAPHORE & flag)) && (NULL == item)){
        return LT_ERR_PARAMETER;
    }

    while(1){
        // This is come from normal task not IRQ
        if(LT_QUEUE_FLAG_FROM_TASK & flag){
            LT_IRQ_disable();
        }

        if(queue->queue_length > queue->ele_number){ // Queue is not full
            if(!(LT_QUEUE_AS_SEMAPHORE & flag)){ // Not semaphore
                memcpy(queue->write_to,item,queue->ele_size);

                queue->write_to = (void*)(((uint32_t)(queue->write_to)) + queue->ele_size);
                if((uint32_t)queue->write_to >= ((uint32_t)(queue->queue_buffer) + (queue->queue_length * queue->ele_size))){
                    queue->write_to = queue->queue_buffer;
                }
            }
            queue->ele_number += 1;

            if(0 != queue->tcb_pending_to_receive->length){
                pending_tcb_item = queue->tcb_pending_to_receive->head;
                LT_list_remove(queue->tcb_pending_to_receive,pending_tcb_item);
                LT_list_insert(ready_queue,pending_tcb_item);
            }

            result = LT_ERR_COMPLETE;
            break;
        }
        else{ // Queue is full
            if(LT_QUEUE_FLAG_FROM_TASK & flag){ // From task, so self pending.
                current_tcb_item = LT_tcb_item_running_task_update();
                // Add to pending list
                LT_list_remove(ready_queue,current_tcb_item);
                LT_list_insert(queue->tcb_pending_to_send,current_tcb_item);
                LT_IRQ_enable();
                // context switch
                hardware_context_switch();
            }
            else{ // From IRQ, stop here
                break;
            }
        }
    }


    if(LT_QUEUE_FLAG_FROM_TASK & flag){
        LT_IRQ_enable();
    }

    return result;
}

LT_error_code_t LT_queue_get(LT_queue_t* queue,void* item,LT_QUEUE_FLAG flag)
{
    LT_TCB_item_t* current_tcb_item = NULL;
    LT_TCB_item_t* pending_tcb_item = NULL;
    LT_error_code_t result = LT_ERR_EMPTY;

    // Empty queue
    if(NULL == queue){
        return LT_ERR_PARAMETER;
    }

    // this is not semaphore but item is empty
    if(!(LT_QUEUE_AS_SEMAPHORE & flag) && (NULL == item)){
        return LT_ERR_PARAMETER;
    }

    while(1){
        //LT_QUEUE_FLAG flag is come from normal task not IRQ
        if(LT_QUEUE_FLAG_FROM_TASK & flag){
            LT_IRQ_disable();
        }

        if(0 < queue->ele_number){
            if(!(LT_QUEUE_AS_SEMAPHORE & flag)){
                memcpy(item,queue->read_from,queue->ele_size);

                queue->read_from = (void*)(((uint32_t)(queue->read_from)) + queue->ele_size);
                if((uint32_t)queue->read_from >= ((uint32_t)(queue->queue_buffer) + (queue->queue_length * queue->ele_size))){
                    queue->read_from = queue->queue_buffer;
                }
            }
            queue->ele_number -= 1;

            if(0 != queue->tcb_pending_to_send->length){
                pending_tcb_item = queue->tcb_pending_to_send->head;
                LT_list_remove(queue->tcb_pending_to_send,pending_tcb_item);
                LT_list_insert(ready_queue,pending_tcb_item);
            }

            result = LT_ERR_COMPLETE;
            break;
        }
        else{
            if(LT_QUEUE_FLAG_FROM_TASK & flag){
                current_tcb_item = LT_tcb_item_running_task_update();
                // Add to pending list
                LT_list_remove(ready_queue,current_tcb_item);
                LT_list_insert(queue->tcb_pending_to_receive,current_tcb_item);
                LT_IRQ_enable();
                // context switch
                hardware_context_switch();
            }
            else{
                break;
            }
        }
    }

    if(LT_QUEUE_FLAG_FROM_TASK & flag){
        LT_IRQ_enable();
    }

    return result;
}

#endif
