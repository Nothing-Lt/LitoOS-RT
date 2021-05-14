/*
 * schedule.h
 *
 *  Created on: 2020��1��23��
 *      Author: 78045
 */

#include "include/schedule.h"

#include "include/task.h"

LT_error_code_t insert_OK(LT_list_item_t volatile * item_in_list, LT_list_item_t volatile* item)
{
    Lito_TCB_t* tcb_item_in_list = NULL;
    Lito_TCB_t* tcb_item = NULL;

    if(NULL == item){
        return LT_ERR_PARAMETER;
    }

    if(NULL == item_in_list){
        return LT_ERR_OK;
    }
    else{
        tcb_item_in_list = (Lito_TCB_t*)(item_in_list->content);
        tcb_item = (Lito_TCB_t*)(item->content);

        if((NULL == tcb_item_in_list) || (NULL == tcb_item)){
            return LT_ERR_PARAMETER;
        }

        if(tcb_item->priority <= tcb_item_in_list->priority){
            return LT_ERR_OK;
        }
    }

    return LT_ERR_FAILED;
}
