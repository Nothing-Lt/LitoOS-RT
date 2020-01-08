/*
 * semaphore_mutex.c
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */
#include "include/semaphore_mutex.h"


void LT_mutex_init(LT_mutex_t* mutex,LT_MUTEX_VALUE init_value)
{
    if(NULL == mutex){
        return;
    }

    *mutex = init_value;
}

LT_error_code_t LT_mutex_lock(LT_mutex_t* mutex)
{
    LT_error_code_t result = LT_ERR_FAILED;

    if(NULL == mutex){
        return LT_ERR_FAILED;
    }

    LT_IRQ_disable();

    if(LT_MUTEX_UNLOCKED == *mutex){
        result = LT_ERR_COMPLETE;
        *mutex = LT_MUTEX_LOCKED;
    }

    LT_IRQ_enable();

    return result;
}

void LT_mutex_unlock(LT_mutex_t* mutex)
{
    if(NULL == mutex){
        return;
    }

    *mutex = LT_MUTEX_UNLOCKED;
}
