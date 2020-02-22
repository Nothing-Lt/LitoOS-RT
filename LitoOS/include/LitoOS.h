/*
 * LitoOS.h
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */

#ifndef INCLUDE_LITOOS_H_
#define INCLUDE_LITOOS_H_


// MODIFY MACRO
#define SPACE_IS_MORE_IMPORTANT 0
#define PERFORMANCE_IS_MORE_IMPORTANT !SPACE_IS_MORE_IMPORTANT

/**
 * @brief Definition of error status, these are mostly used as return value.
 */
typedef enum{
	LT_ERR_COMPLETE  = 0, /*!< LT_ERR_COMPLETE */
	LT_ERR_OK        = LT_ERR_COMPLETE, /*!< LT_ERR_OK */
	LT_ERR_FAILED    = 1, /*!< LT_ERR_FAILED */
	LT_ERR_NULL      = 2, /*!< LT_ERR_NULL */
	LT_ERR_FULL      = 3, /*!< LT_ERR_FULL */
	LT_ERR_EMPTY     = 4, /*!< LT_ERR_EMPTY */
	LT_ERR_UNKNOWN   = 5, /*!< LT_ERR_UNKNOWN */
	LT_ERR_PARAMETER = 6, /*!< LT_ERR_PARAMETER */
	LT_ERR_NOT_FOUND = 7  /*!< LT_ERR_NOT_FOUND */
}LT_error_code_t;

/**
 * @brief Definition of the scheduling status.
 */
typedef enum{
	LT_SCHEDULE_RUNNING = 1,   /*!< LT_SCHEDULE_RUNNING*/
	LT_SCHEDULE_NOT_RUNNING = 2/*!< LT_SCHEDULE_NOT_RUNNING*/
}LT_SCHEDULE_STATUS;

/**
 * @brief A macro to calculate the offset of a member in one structure.
 */
#define OFFSET(a,b) ((uint32_t)(&(((a*)0)->b)-0))

/**
 * @brief Initialize the LitoOS. This function must be called after the hardware initialization but before create new tasks.
 */
void Lito_init();

/**
 * @brief Start the LitoOS, including start the schedular.
 *        This function must be called if developer finished create new tasks and wants the system to be running.
 */
void Lito_start();

#endif /* INCLUDE_LITOOS_H_ */
