/*
In this file, implement the real-time scheduling algorithm,
and in task.c, we will use those real-time scheduling algorithm defined here. 
*/

#include <schedule.h>

#include <stdint.h>
#include <task.h>

// Ready queue is maintained by task.c
// Running queue is maintained by schedule.c
extern Lito_TCB* ready_queue;
Lito_TCB* running_queue[CPU_NUM];


void EDF_initialize();

int32_t EDF_insert_OK(Lito_TCB* tcb1, Lito_TCB* tcb2);

void EDF_running_queue_reorganize();

void EDF_scheduling(Lito_TCB* tcb_p[CPU_NUM],uint32_t* next_call);

void EDF_job_exit();

void EDF_algorithm_exit();


SCHEDULING_ALGORITHM sa = {
    .name           = "EDF",
    .insert_OK      = EDF_insert_OK,
    .initialize     = EDF_initialize,
    .reorganize     = EDF_running_queue_reorganize,
    .scheduler      = EDF_scheduling,
    .job_exit       = EDF_job_exit,
    .algorithm_exit = EDF_algorithm_exit,
};

void EDF_initialize()
{
    int32_t i;
    for (i = 0; i < CPU_NUM; i++)
    {
        running_queue[i] = NULL;
    }
}

int32_t EDF_insert_OK(Lito_TCB* tcb1, Lito_TCB* tcb2)
{
    if(NULL == tcb2)
    {
        return 0;
    }

    if(NULL == tcb1)
    {
        return 1;
    }

    if(tcb1->deadline >= tcb2->deadline)
    {
        return 1;
    }
    
    return 0;
}

void EDF_running_queue_reorganize()
{
}

/*

*/
void EDF_scheduling(Lito_TCB* tcbs[CPU_NUM], uint32_t* next_call)
{
    uint32_t cpu_id = 0;
    uint32_t finish_min = UINT_MAX;

    Lito_TCB* tcb_p = NULL;

    for(tcb_p = ready_queue ; tcb_p && (cpu_id < CPU_NUM); tcb_p = tcb_p->next)
    {
        if(0 < tcb_p->rect)
        {
            tcbs[cpu_id++] = tcb_p;
            
            if(finish_min > tcb_p->rect)
            {
                finish_min = tcb_p->rect;
            }
        }
    }

    *next_call = finish_min;
}

void EDF_job_exit()
{

}

void EDF_algorithm_exit()
{

}