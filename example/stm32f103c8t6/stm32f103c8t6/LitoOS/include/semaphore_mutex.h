/*
 * semaphore_mutex.h
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */

#ifndef INCLUDE_SEMAPHORE_MUTEX_H_
#define INCLUDE_SEMAPHORE_MUTEX_H_

#include "LitoOS.h"
#include "queue.h"

/**
 * @brief A set of constant variable to describe the state of a mutex
 */
typedef enum{
	LT_MUTEX_LOCKED = 0, /*!< LT_MUTEX_LOCKED, this mutex is locked */
	LT_MUTEX_UNLOCKED = 1 /*!< LT_MUTEX_UNLOCKED this mutex is not locking*/
}LT_MUTEX_VALUE;

/**
 * @brief Definition of LT_mutex_t
 */
typedef LT_MUTEX_VALUE LT_mutex_t;

/**
 * @brief Definition of LT_semaphore_t
 */
typedef LT_queue_t LT_semaphore_t;

/**
 * @brief Initialize mutex_t variable.
 * @param[in] mutex A pointer pointing to a LT_mutex_t variable.
 * @param[in] init_value initialization value for this mutex variable.
 */
void LT_mutex_init(LT_mutex_t* mutex,LT_MUTEX_VALUE init_value);

/**
 * @brief Lock LT_mutex_t variable. This is not a blocking function, if it is impossible to lock this variable, just return the result.
 * @param[in] mutex LT_mutex_t pointer.
 * @retval LT_ERR_COMPLETE Successfully lock this mutex.
 * @retval LT_ERR_FAILED Failed to lock this mutex.
 */
LT_error_code_t LT_mutex_lock(LT_mutex_t* mutex);

/**
 * @brief Unlock LT_mutex_t variable.Release a mutex.
 * @param[in] mutex LT_mutex_t pointer.
 */
void LT_mutex_unlock(LT_mutex_t* mutex);

/**
 * @brief Create a semaphore, and initialized as semaphore_size.
 * @param[in] semaphore_size Specify the semaphore size
 * @return An pointer pointing at a semaphore variable, if it is NULL, this means failed to create this semaphore.
 */
#define LT_semaphore_create(semaphore_size) LT_queue_create(semaphore_size,0)

/**
 * @brief Get a semaphore.
 * @param[in] semaphore a pointer,pointing at a semaphore variable.
 * @param[in] flag LT_QUEUE_FLAG, if it is a task to take this semaphore, then flag=LT_QUEUE_FLAG_FROM_TASK.
 * 			  if it is a IRQ to take this semaphore, then flag=LT_QUEUE_FLAG_FROM_IRQ.
 * @retval LT_ERR_COMPLETE This operation is completed.
 * @retval LT_ERR_PARAMETER This operation is failed because of parameter.
 * @retval LT_ERR_EMPTY This operation is failed because of this semaphore is empty.
 */
#define LT_semaphore_get(semaphore,flag) LT_queue_get(semaphore,NULL,flag|LT_QUEUE_AS_SEMAPHORE)

/**
 * @brief Release a semaphore.
 * @param[in] semaphore a pointer,pointing at a semaphore variable.
 * @param[in] flag LT_QUEUE_FLAG, if it is a task to give this semaphore, then flag=LT_QUEUE_FLAG_FROM_TASK.
 * 			  if it is a IRQ to give this semaphore, then flag=LT_QUEUE_FLAG_FROM_IRQ.
 * @retval LT_ERR_COMPLETE This operation is completed.
 * @retval LT_ERR_PARAMETER This operation is failed because of parameter.
 * @retval LT_ERR_FULL This operation is failed because of this semaphore is full.
 */
#define LT_semaphore_put(semaphore,flag) LT_queue_put(semaphore,NULL,flag|LT_QUEUE_AS_SEMAPHORE)

/**
 * @brief Get a semaphore.
 * @param[in] semaphore a pointer,pointing at a semaphore variable.
 * @param[in] flag LT_QUEUE_FLAG, if it is a task to take this semaphore, then flag=LT_QUEUE_FLAG_FROM_TASK.
 *            if it is a IRQ to take this semaphore, then flag=LT_QUEUE_FLAG_FROM_IRQ.
 * @retval LT_ERR_COMPLETE This operation is completed.
 * @retval LT_ERR_PARAMETER This operation is failed because of parameter.
 * @retval LT_ERR_EMPTY This operation is failed because of this semaphore is empty.
 */
#define LT_semaphore_get_from_ISR(semaphore,flag,ask_for_scheduling) LT_queue_get_from_ISR(semaphore,NULL,flag|LT_QUEUE_AS_SEMAPHORE,ask_for_scheduling)

/**
 * @brief Release a semaphore.
 * @param[in] semaphore a pointer,pointing at a semaphore variable.
 * @param[in] flag LT_QUEUE_FLAG, if it is a task to give this semaphore, then flag=LT_QUEUE_FLAG_FROM_TASK.
 *            if it is a IRQ to give this semaphore, then flag=LT_QUEUE_FLAG_FROM_IRQ.
 * @retval LT_ERR_COMPLETE This operation is completed.
 * @retval LT_ERR_PARAMETER This operation is failed because of parameter.
 * @retval LT_ERR_FULL This operation is failed because of this semaphore is full.
 */
#define LT_semaphore_put_from_ISR(semaphore,flag,ask_for_scheduling) LT_queue_put_from_ISR(semaphore,NULL,flag|LT_QUEUE_AS_SEMAPHORE,ask_for_scheduling)


#endif /* INCLUDE_SEMAPHORE_MUTEX_H_ */
