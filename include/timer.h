
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <interrupt.h>

typedef struct
{
	uint32_t   pid;
	EVENT_FLAG flag;
	uint32_t   trigger_time;
	void*      dev;
}TIMER_EVENT_DESC;

void LT_timer_init();

int32_t LT_timer_event_register(uint32_t trigger_time, EVENT_FLAG flag, uint32_t pid, void* function, Lito_task* task);

uint32_t LT_timer_event_remove(uint32_t timer_idx);


#endif