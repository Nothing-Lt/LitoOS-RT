/*
 * task.h
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */

#ifndef INCLUDE_TASK_H_
#define INCLUDE_TASK_H_

#include <sys/types.h>

#include "LitoOS.h"
#include "list.h"

/**
 * @brief Task status.
 */
typedef enum{
    RUNNING = 0x1,/*!< RUNNING */
    READY   = 0x2,/*!< READY */
    PENDING = 0x4,/*!< PENDING */
}Lito_TASK_STATUS;

typedef enum{
    NO_SCHEDULING = 1,
    ASK_FOR_SCHEDULING = 2
}LT_SCHEDULE_FLAG_t;

/**
 * @brief Definition of task function.
 * @param param Parameter for this function.
 */
typedef void task_func(const void* param);

/**
 * @brief Definition of task structure. This structure only used in creating new task.
 */
typedef struct Lito_task_t
{
    pid_t      pid;
    uint32_t   flag;      // This task is periodic or aperiodic
    uint32_t   priority;
    size_t     stack_size;
    void*      parameter;
    task_func* function;  // Entry point of this task
}Lito_task_t;


/**
 * @brief Definition of TCB structure for LitoOS.
 */
typedef struct Lito_TCB_t
{
    pid_t      pid;
    uint32_t   status;         // process status: running, waiting, hanging
    uint32_t   priority;       // dynamic priority,this priority will be decide in running time
    uint32_t   deadline;       // Absolute deadline, will be decided in running time
    task_func* function;
    size_t     stack_size;
    TCB_t      tcb;            // When you adapt this system to other platform, modify this!!!!!!!!
}Lito_TCB_t;

/**
 * @brief Definition of LT_TCB_list_t.
 */
typedef LT_list_t LT_TCB_list_t;

/**
 * @brief Difinition of LT_TCB_item_t.
 */
typedef LT_list_item_t LT_TCB_item_t;

/**
 * @brief Initialize ready queue.
 * @retval LT_ERR_COMPLETE This operation is completed.
 * @retval LT_ERR_FAILED Failed to initialize the ready queue.
 */
LT_error_code_t LT_ready_queue_init();


/**
 * @brief Insert one TCB into ready_queue.
 * @param[in] tcb The address of LT_TCB_item_t variable, which will be inserted into ready_queue.
 * @retval LT_ERR_COMPLETE This operation is completed.
 * @retval LT_ERR_PARAMETER This operation failed because of the parameter.
 */
LT_error_code_t LT_ready_queue_insert(LT_TCB_item_t* tcb);


/**
 * @brief Remove one TCB from ready queue.
 * @param[in] tcb The TCB which will be removed from ready queue.
 * @retval LT_ERR_COMPLETE This operation is completed
 * @retval LT_ERR_PARAMETER Error with parameters, might because list or item is NULL.
 * @retval LT_ERR_EMPTY Ready queue is empty.
 * @retval LT_ERR_NOT_FOUND This TCB is not found from ready queue.
 */
LT_error_code_t LT_ready_queue_remove(LT_TCB_item_t* tcb);

/**
 * @brief Create new task.
 * @param task The address of Lito_tasl_t variable.
 * @retval The address of TCB for created task, if it is NULL, it is failed to create new task.
 */
LT_TCB_item_t* LT_task_create(Lito_task_t* task);

/**
 * @brief Switch to next task.
 */
void LT_task_switch();

/**
 * @brief Update the current running tcb.
 * @return The tcb_item before update.
 */
void LT_tcb_item_running_task_update();

/**
 * @brief Get my TCB.
 * @return The address of my TCB.
 */
LT_TCB_item_t* LT_TCB_get();

#endif /* INCLUDE_TASK_H_ */
