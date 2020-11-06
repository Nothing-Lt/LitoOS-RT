/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f1xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include <stm32.h>
#include <stdio.h>
#include <stdlib.h>

#include "stm32f1xx_it.h"

#include "../LitoOS/include/task.h"
#include "../LitoOS/include/timer.h"
#include "../LitoOS/include/semaphore_mutex.h"

#include "../Inc/stm32.h"

extern TCB_t* tcb_running;
extern LT_timer_event_list_t* timer_event_list;
extern LT_SCHEDULE_STATUS lt_schedule_status;

/******************************************************************************/
/*           Cortex-M3 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{

}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  while (1)
  {

  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{

  while (1)
  {

  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{

  while (1)
  {

  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{

  while (1)
  {

  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
void __attribute__((naked)) SVC_Handler(void)
{

	__asm volatile(
			"	mov r0, %[stack_top]			\n" /* The first item in pxCurrentTCB is the task top of stack. */
			"   ldr r0,[r0]                     \n"
	                "   ldr r0,[r0]                     \n"
			"	ldmia r0!, {r4-r11}				\n" /* Pop the registers that are not automatically saved on exception entry and the critical nesting count. */
			"	msr psp, r0						\n" /* Restore the task stack pointer. */
			"	isb								\n"
			"	mov r0, #0 						\n"
			"	msr	basepri, r0					\n"
			"	orr r14, #0xd					\n"
			"	bx r14							\n"
			::[stack_top]"r"(&tcb_running):);
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{

}

/**
  * @brief This function handles Pendable request for system service.
  */
void __attribute__((naked)) PendSV_Handler(void)
{
    __asm volatile(
            "mov   r3, %[stack_save]            \n"
            "ldr   r2,[r3]                      \n"
            "mrs   r0, psp                      \n"
            "isb                                \n"
            "stmdb r0!, {r4-r11}                \n" // Save the remaining registers.
            "str   r0, [r2]                     \n" // Save the new top of stack into the first member of the TCB.
            "stmdb sp!,{r3,r14}                 \n"
            "bl LT_tcb_item_running_task_update \n"
            "ldmia sp!,{r3,r14}                 \n"
            "ldr   r2, [r3]                     \n"
            "ldr   r0, [r2]                     \n"
            "ldmia r0!, {r4-r11}                \n" // Pop the registers.
            "msr psp, r0                        \n"
            "isb                                \n"
            "bx r14                             \n"
            ::[stack_save]"r"(&tcb_running)
    );
}

/**
  * @brief This function handles System tick timer.
  */
void SysTick_Handler(void)
{
	uint32_t current_tick = 0;
	LT_SCHEDULE_FLAG_t ask_for_scheduling = NO_SCHEDULING;
	LT_SCHEDULE_FLAG_t will_schedule = NO_SCHEDULING;
	LT_timer_event_t* timer_event = NULL;
	LT_timer_event_item_t* timer_event_item = NULL;
	LT_timer_event_item_t* timer_event_item_free = NULL;

	HAL_IncTick();
	current_tick = HAL_GetTick();

	// Check the timer event.
	if((NULL != timer_event_list) && (0 != timer_event_list->length)){
		timer_event_item = timer_event_list->head;
		while(timer_event_item){
			timer_event = (LT_timer_event_t*)timer_event_item->content;
			if((NULL != timer_event) && (current_tick >= timer_event->issue_at)){
				if(LT_TIMER_EVENT_FUNCTION & timer_event->flag){
					(timer_event->handler)();
				}
				else if(LT_TIMER_EVENT_SEMAPHORE & timer_event->flag){
					LT_semaphore_put_from_ISR(timer_event->semaphore_queue,LT_QUEUE_FLAG_FROM_IRQ,&ask_for_scheduling);
					will_schedule |= ask_for_scheduling;
				}

				// This event already been issued, so remove it from timer event list.
				timer_event_item_free = timer_event_item;
				timer_event_item = timer_event_item->next;
				LT_list_remove(timer_event_list,timer_event_item_free);
				free(timer_event_item_free);
				timer_event_item_free = NULL;
			}
			else{
				timer_event_item = timer_event_item->next;
			}
		}
	}

	// The scheduling is not started yet
    if(LT_SCHEDULE_RUNNING != lt_schedule_status){
        return;
    }

	if(ASK_FOR_SCHEDULING & will_schedule){
		LT_task_switch();
	}
}

/******************************************************************************/
/* STM32F1xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f1xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
