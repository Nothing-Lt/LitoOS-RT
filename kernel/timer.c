#include <timer.h>

#include <util.h>
#include <stdint.h>
#include <task.h>
#include <interrupt.h>

uint32_t system_time;

TIMER_EVENT_DESC timer_event_table[MINOR_DEV_NUMBER];


void timer_handler()
{

}

/*
    Initialize timer IRQ line and timer event table
*/
void LT_timer_init()
{
    uint32_t idx = 0;
    
    // Bind timer handler to 0x20 IRQ line.
    sys_IRQLINE_set(0x20,timer_handler);

    // Set all desc to unused
    for(idx = 0 ; idx < MINOR_DEV_NUMBER ; idx++)
    {
        timer_event_table[idx].flag = FLAG_UNUSED;
    }
}

/*
    Register timer event.
    Parameter:
        trigger_time, the time this event should happen.
        flag, for specifying the event flag
        pid, for specifying the pid
        function, the hook function
        task, the task
    Return value:
        0, Failed
        Other, Success
*/
int32_t LT_timer_event_register(uint32_t trigger_time, EVENT_FLAG flag, uint32_t pid, void* function, Lito_task* task)
{
    uint32_t idx = 0;

    if(trigger_time < system_time)
    {
        return -1;
    }

    if(FLAG_FUNCTION == flag)
    {
        if(NULL == function)
        {
            return -1;
        }
    }

    if((FLAG_TASK == flag) || (FLAG_MESSAGE == flag))
    {
        if(NULL == task)
        {
            return -1;
        }
    }

    for(idx = 0 ; idx < MINOR_DEV_NUMBER ; idx++)
    {
        if(FLAG_UNUSED == timer_event_table[idx].flag)
        {
            break;
        }
    }
    if(MINOR_DEV_NUMBER == idx)
    {
        return -1;
    }

    timer_event_table[idx].flag = flag;
    timer_event_table[idx].pid = task->pid;
    timer_event_table[idx].trigger_time = trigger_time;

    if(FLAG_FUNCTION == flag)
    {
        timer_event_table[idx].dev = function;
    }
    else
    {
        timer_event_table[idx].dev = task;
    }

    return idx;
}

/*
    Remove the registered timer event
    Parameter:
        timer_idx, For specifying the index of timer event desc
    Return value: 
        0, Failed
        1, Success
*/
uint32_t LT_timer_event_remove(uint32_t timer_idx)
{
    if(MINOR_DEV_NUMBER <= timer_idx)
    {
        return 0;
    }

    timer_event_table[timer_idx].flag = FLAG_UNUSED;

    return 1;
}