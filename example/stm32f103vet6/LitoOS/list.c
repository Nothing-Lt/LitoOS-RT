/*
 * list.c
 *
 *  Created on: Sep 26, 2019
 *      Author: linaqin
 */
#include "include/list.h"

#include <stdlib.h>
#include <sys/types.h>

#include "include/LitoOS.h"

LT_list_t* LT_list_create()
{
	LT_list_t* new_list = NULL;

	new_list = (LT_list_t*)malloc(sizeof(LT_list_t));
	if(NULL == new_list){
		return NULL;
	}

	if(LT_ERR_COMPLETE!= LT_list_init(new_list)){
		free(new_list);
		return NULL;
	}

	return new_list;
}

LT_error_code_t LT_list_init(LT_list_t* list)
{
	if(NULL == list){
		return LT_ERR_PARAMETER;
	}

	list->length = 0;
	list->head = list->end = NULL;

	return LT_ERR_COMPLETE;
}


LT_error_code_t LT_list_insert(LT_list_t* list,LT_list_item_t* item)
{
	if((NULL == list) || (NULL == item)){
		return LT_ERR_PARAMETER;
	}

	if(0 == list->length){
		list->head = list->end = item;
	}
	else{
		item->prev = list->end;
		list->end->next = item;
		list->end = item;
	}
	(list->length)++;

	return LT_ERR_COMPLETE;
}

LT_error_code_t LT_list_remove(LT_list_t* list,LT_list_item_t* item)
{
	LT_list_item_t* ele = NULL;

	if((NULL == list) || (NULL == item)){
		return LT_ERR_PARAMETER;
	}

	if(0 == list->length){
		return LT_ERR_EMPTY;
	}

	if(list->head == item){
		(list->length)--;
		list->head = list->head->next;
        if(NULL != list->head){
		    list->head->prev = NULL;
        }

        if(list->end == item){
            list->end = list->end->next;
        }
		return LT_ERR_COMPLETE;
	}

	if(list->end == item){
		(list->length)--;
		list->end = list->end->prev;
        if(NULL != list->end){
		    list->end->next = NULL;
        }

        if(list->head == item){
            list->head = list->head->prev;
        }
		return LT_ERR_COMPLETE;
	}

	for(ele = list->head ; ele ; ele = ele->next){
		if(ele == item){
			(list->length)--;
			ele->prev->next = ele->next;
			ele->next->prev = ele->prev;
			break;
		}
	}

	if(NULL == ele){
		return LT_ERR_NOT_FOUND;
	}

	return LT_ERR_COMPLETE;
}