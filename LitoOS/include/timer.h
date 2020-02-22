/**
 * @file timer.h
 * The definition of timer in LitoOS.
 * Developers can create a timer queue,
 * if it is the time to trigger,
 * it will execute the function called handler or put an element into semaphore queue.
 *
 * @author linaqin
 * @date 2019/09/26
 */

#ifndef INCLUDE_TIMER_H_
#define INCLUDE_TIMER_H_

#include <sys/types.h>

#include "LitoOS.h"
#include "list.h"
#include "semaphore_mutex.h"

typedef enum{
	LT_TIMER_EVENT_FUNCTION = 1,
	LT_TIMER_EVENT_SEMAPHORE = 2
}LT_TIMER_EVENT_FLAG;

/**
 * @brief Definition of handler function.
 */
typedef void handler_func();

/**
 * @brief Definition of timer structure.
 */
typedef struct{
	LT_TIMER_EVENT_FLAG flag;
	uint32_t            issue_at;        /*!< The handler will be executed now. */
	handler_func*       handler;         /*!< The handler function will be executed. */
	LT_semaphore_t*     semaphore_queue; /*!< The semaphore queue */
}LT_timer_event_t;

/**
 * @brief Definition of LT_timer_event_list_t.
 */
typedef LT_list_t LT_timer_event_list_t;

/**
 * @brief Definition of LT_timer_event_item_t
 */
typedef LT_list_item_t LT_timer_event_item_t;

/**
 * @brief Initialize timer event list.
 */
LT_error_code_t LT_timer_init();

/**
 * @brief Register a timer event.
 * @param[out] timer_event_handle Is the timer_event handle, this will be used to remove this timer event from list.
 * @param[in] issue_at Specify the time that issue this timer event.
 * @param[in] handler The function pointer will be executed at issue_at, if developer set.
 * @param[in] semaphore_queue The semaphore_queue.
 * @param[in] flag A flag that specify this timer event is execute a function or put a semaphore into a semaphore queue.
 * @retval LT_ERR_COMPLETE This insertion is finished successfully.
 * @retval LT_ERR_PARAMETER Error with parameter.
 * @retval LT_ERR_FAILED This operation is failed, might because of malloc returned NULL.
 */
LT_error_code_t LT_timer_event_regist(LT_timer_event_item_t** timer_event_handle,uint32_t issue_at, handler_func* handler, LT_semaphore_t* semaphore_queue, LT_TIMER_EVENT_FLAG flag);

/**
 * @brief Remove a registered timer event.
 * @param[in] timer_event_handle
 * @retval LT_ERR_PARAMETER Error with the parameter, might because the parameter is a NULL pointer.
 * @retval LT_ERR_COMPLETE Finished this operation successfully.
 * @retval LT_ERR_EMPTY timer_event_list has no element.
 * @retval LT_ERR_NOT_FOUND This timer_event_item is not found in timer_event_list.
 */
LT_error_code_t LT_timer_event_remove(LT_timer_event_item_t* timer_event_handle);

#endif /* INCLUDE_TIMER_H_ */
