/*
 * queue.h
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */

#ifndef INCLUDE_QUEUE_H_
#define INCLUDE_QUEUE_H_

#include <stdio.h>

#include "LitoOS.h"
#include "task.h"

/**
 * Definition of Queue flag.
 */
typedef enum{
    LT_QUEUE_FLAG_WAIT    = 1,  //!< LT_QUEUE_FLAG_WAIT, Task will be waiting for sending or receiving.
    LT_QUEUE_FLAG_NO_WAIT = 2,  //!< LT_QUEUE_FLAG_NO_WAIT, Task will not wait for sending or receiving
    LT_QUEUE_FLAG_FROM_TASK = 4,//!< LT_QUEUE_FLAG_FROM_TASK, This request is from task.
    LT_QUEUE_FLAG_FROM_IRQ  = 8,//!< LT_QUEUE_FLAG_FROM_IRQ, This request is form IRQ
    LT_QUEUE_AS_SEMAPHORE   = 16   //!< LT_QUEUE_AS_SEMAPHORE, This queue is for semaphore.
}LT_QUEUE_FLAG;

/**
 *
 */
typedef struct{
    uint32_t ele_size;                       //!< Element size
    uint32_t ele_number;                     //!< Element number
    uint32_t queue_length;                   //!< The length of this queue
    void* queue_buffer;                      //!< The buffer for this queue
    void* read_from;                         //!< The reading pointer
    void* write_to;                          //!< The writing pointer
#if 1 == PERFORMANCE_IS_MORE_IMPORTANT
    LT_TCB_list_t* tcb_pending_to_receive;  //!< For keeping the pending task because of waiting for this semaphore or waiting for sending semaphore.
    LT_TCB_list_t* tcb_pending_to_send;     //!< For keeping the pending task because of waiting to send this semaphore or item.
#endif
}LT_queue_t;

/**
 * Initialize a queue.
 * @param queue The pointer of a queue.
 * @param queue_length The length of this queue.
 * @param ele_size The element size for this queue.
 * @param queue_buffer The buffer for this queue.
 */
void LT_queue_init(LT_queue_t* queue,uint32_t queue_length,size_t ele_size,void* queue_buffer);

/**
 * Create a new queue, and initialize this queue.
 * @param queue_length The maximum length of this queue.
 * @param ele_size The Size of element in this queue.
 * @return The pointer of this created queue. If it is NULL, this means it failed to create this queue.
 */
LT_queue_t* LT_queue_create(uint32_t queue_length,size_t ele_size);

/**
 * Put a new element into this queue.
 * @param queue The pointer of this queue.
 * @param item The pointer of the item which will be put into this queue.
 * @param flag The queue flag.
 * @retval LT_ERR_PARAMETER Wrong parameter is given.
 * @retval LT_ERR_COMPLETE It is success to put a new element into this queue.
 * @retval LT_ERR_FULL This queue is full, cannot put.
 */
LT_error_code_t LT_queue_put(LT_queue_t* queue,void* item,LT_QUEUE_FLAG flag);

/**
 * Get an element from this queue.
 * @param queue The pointer of this queue.
 * @param item The pointer of the item which receive from this queue.
 * @param flag The queue flag.
 * @retval LT_ERR_PARAMETER Wrong parameter is given.
 * @retval LT_ERR_COMPLETE It is success to put a new element into this queue.
 * @retval LT_ERR_EMPTY This queue is full, cannot put.
 */
LT_error_code_t LT_queue_get(LT_queue_t* queue,void* item,LT_QUEUE_FLAG flag);

#endif /* INCLUDE_QUEUE_H_ */
