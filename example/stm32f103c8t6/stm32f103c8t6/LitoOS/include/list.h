/*
 * list.h
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */

#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

#include <sys/types.h>
#include "LitoOS.h"

/**
 * @brief Definition of item in list.
 */
typedef struct lt_list_item{
	void* content;             /*!< Pointer pointing at the address of content */
	struct lt_list_item* next; /*!< Point to the next item */
	struct lt_list_item* prev; /*!< Point to the previous item */
}LT_list_item_t;

/**
 * @brief Definition for insertion function. This function is for telling it is okay to insert
 * current item to this position.
 */
typedef LT_error_code_t insert_func(LT_list_item_t*, LT_list_item_t*);

/**
 * @brief Definition of one list.
 */
typedef struct{
	uint32_t     length;  /*!< Current length of this list */
	insert_func* insert_OK;
	LT_list_item_t* head; /*!< Point to the first item in this list */
	LT_list_item_t* end;  /*!< Point to the last item in this list */
}LT_list_t;

/**
 * @brief Create a list.
 * @param[in] insert_OK The function to decide the new item is okay to insert at this position.
 * @return The address of created list, if it is NULL, this means failed to create a list.
 *         The reason why this happen is because of failed of malloc function.
 */
LT_list_t* LT_list_create(insert_func* insert_OK);

/**
 * @brief Initialize a list.
 * @param[in] list The address of a LT_list_t variable.
 * @param[in] insert_OK The function to decide the new item is okay to insert at this position.
 * @retval LT_ERR_COMPLETE Initialization operation is completed.
 * @retval LT_ERR_PARAMETER Error with the parameter, list is NULL?
 */
LT_error_code_t LT_list_init(LT_list_t* list,insert_func* insert_OK);

/**
 * @brief Insert one item into list.
 * @param[in] list Pointer of LT_list_t.
 * @param[in] item The address of the item which will be inserted into list.
 * @retval LT_ERR_COMPLETE This operation is completed.
 * @retval lt_err_PARAMETER Wrong parameter, might because the list or item is NULL.
 */
LT_error_code_t LT_list_insert(LT_list_t* list,LT_list_item_t* item);

/**
 * @brief Remove one item from list.
 * @param[in] list Pointer of the list.
 * @param[in] item The address of the item which will be removed from list.
 * @retval LT_ERR_COMPLETE Complete the remove operation.
 * @retval LT_ERR_PARAMETER Error with parameters, might because list or item is NULL.
 * @retval LT_ERR_EMPTY This list is empty.
 * @retval LT_ERR_NOT_FOUND This item is not found from this list.
 */
LT_error_code_t LT_list_remove(LT_list_t* list,LT_list_item_t* item);

#endif /* INCLUDE_LIST_H_ */
