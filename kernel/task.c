#include <task.h>
#include <memory.h>
#include <interrupt.h>

#include "../arch/x86/x86.h"
#include "../arch/x86/x86_task.h"
#include "../arch/x86/interrupt/x86_interrupt.h"

task_list* task_l;
TCB_list* TCB_l;
Lito_running_queue* running_queue;

volatile uint32_t pid;

/*
Initial task list 
Parameter:
    No
Return value:
    0: falied(because malloc)
    1: successed
*/
int LT_task_list_init()
{
    int i;

    task_l = (task_list*)malloc(sizeof(task_list));
    if(task_l == NULL){return 0;}
    
    pid                 = 0;
    task_l->task_number = 0;
    for(i=0; i<MAX_TASK_NUMBER; i++)
    {
        task_l->list[i] = NULL;
    }

    return 1;
}


/*
initial the TCB list
Parameter:
    No
Return value:
    0: failed (might because some mistake occured in malloc)
    1: succesed
*/
int LT_TCB_list_init()
{
    int i;
    
    TCB_l = (TCB_list*)malloc(sizeof(TCB_list));
    if(TCB_l == NULL){return 0;}

    TCB_l->tcb_number = 0;
    for(i=0; i<MAX_TCB_NUMBER; i++)
    {
        TCB_l->list[i] = NULL;
    }

    return 1;
}

/*
Initialize the running queue
Parameter:
    No
Return value:
    0:failed
    1:Successed
*/
int LT_running_queue_init()
{
    int i;

    running_queue = (Lito_running_queue*)malloc(sizeof(Lito_running_queue));
    if(running_queue == NULL){return 0;}

    for(i=0;i<MAX_PRIORITY;i++)
    {
        running_queue->list[i] = NULL;
    }
    running_queue->tcb_number = 0;

    return 1;
}

/*
Insert tcb block into TCB list
Parameter:
    a pointer point to an Lito_TCB instant
Return value:
    0: Failed
    1: Successed
*/
int TCB_list_insert(Lito_TCB* tcb)
{
    int i;

    if(TCB_l==NULL || tcb==NULL){return 0;}

    if(TCB_l->tcb_number >= MAX_TCB_NUMBER){return 0;}
    
    for(i=0;i<MAX_TCB_NUMBER;i++)
    {
        if(TCB_l->list[i] == NULL)
        {
            TCB_l->list[i] = tcb;
            TCB_l->tcb_number++;
            return 1;
        }
    }

    return 0;
}

/*
Remove an element from TCB list
Parameter:
    process id of the element you want to remove
Retuen value:
    NULL: Failed
    Pointer of TCb: Successed
*/
Lito_TCB* TCB_list_remove(uint32_t pid)
{
    int32_t i;
    Lito_TCB* result = NULL;
 
    if(TCB_l==NULL || pid==0){return NULL;}

    for(i=0;i<MAX_TCB_NUMBER;i++)
    {
        if(TCB_l->list[i]!=NULL && TCB_l->list[i]->pid==pid)
        {
            result = TCB_l->list[i];
            TCB_l->list[i] = NULL;
            TCB_l->tcb_number--;
            return result;
        }
    }
    return NULL;
}

/*
Insert an element into Lito_task list
Parameter:
    a pointer point to an Lito_task instant
Return value:
    0: Failed
    1: Successed
*/
int32_t task_list_insert(Lito_task* task)
{
    int32_t i;

    if(task_l==NULL || task==NULL){return 0;}

    if(task_l->task_number >= MAX_TASK_NUMBER){return 0;}

    for(i=0;i<MAX_TASK_NUMBER;i++)
    {
        if(task_l->list[i] == NULL)
        {
            task_l->list[i] = task;
            task_l->task_number++;
            return 1;
        }
    }

    return 0;
}

/*
Remove an element from task_list
Parameter:
    process id of the element you want to remove
Return value:
    NULL: Failed
    Pointer of Lito_task: Successed
*/
Lito_task* task_list_remove(uint32_t pid)
{
    int32_t i;
    Lito_task* result = NULL;

    if(task_l==NULL || pid==0){return NULL;}

    for(i=0;i<MAX_TASK_NUMBER;i++)
    {
        if(task_l->list[i]!=NULL && task_l->list[i]->pid==pid)
        {
            result = task_l->list[i];
            task_l->list[i] = NULL;
            task_l->task_number--;
            return result;
        }
    }
    return NULL;
}

/*
Insert TCB into running queue
parameter:
    tcb: Pointer point to an Lito_task instance
Return value:
    0:Failed
    1:Successed
*/
int running_queue_insert(Lito_TCB* tcb)
{
    uint32_t tmp_priority = 0;
    
    // Security check
    if(running_queue==NULL || tcb==NULL || tcb->priority>=MAX_PRIORITY || tcb->priority<1){return 0;}

    // Insert into running queue
    tmp_priority = tcb->priority-1;
    tcb->next = running_queue->list[tmp_priority];
    running_queue->list[tmp_priority] = tcb;
    running_queue->tcb_number++;

    return 1;
}

/*
Remove the TCB from running queue
Parameter:
    pid: the pid of TCB which you want to remvoe from running queue
Return value:
    NULL: Failed
    Pointer of Lito_TCB: Susscced
*/
Lito_TCB* running_queue_remove(uint32_t pid)
{
    int   i = 0; 
    Lito_TCB*  result      = NULL;
    Lito_TCB** tcb_pointer = NULL;

    if(running_queue == NULL||running_queue->tcb_number==0){return NULL;}

    for(i=0;i<MAX_PRIORITY;i++)
    {
        tcb_pointer = &(running_queue->list[i]);
        for(;*tcb_pointer!=NULL;tcb_pointer=&((*tcb_pointer)->next))
        {
            if((*tcb_pointer)->pid==pid)
            {
                result       = *tcb_pointer;
                *tcb_pointer = result->next;
                return result;
            }
        }
    }
    
    return NULL;
}

/* 
Parameter:
   Lito_task structure
Return value:
   0      :failed to create new task
   others :Success
*/
uint32_t LT_create_task(Lito_task* task)
{

    if(task == NULL){return 0;}

    task_list_insert(task);


    if(task->flag&TG_CLOCK_EVENT)
    {
        /* those tasks triggered by Clock interruption,
           most for periodtc tasks */
        if(!IRQ_trigger_set(CLOCK_IRQ_LINE,task->flag,task)){while(1);}
    }
    else if(task->flag&TG_EXTERNAL_EVENT)
    {
        /* Those tasks triggered by External interruption,
           most for aperiodic tasks */
        if(!IRQ_trigger_set(task->extra,task->flag,task)){while(1);}
    }
    else if(task->flag&NORMAL_TASK)
    {
        /* Those normal tasks,just run once, and maybe no deadline,
           start them immediately*/
        if(!LT_activate_task(task)){while(1);}
    }

    return 1;
}

/*
Activativate specific task
Parameter:
   A pointer point at a Lito_task instant
Return value:
   1: success
   0: otherwise
*/
int32_t LT_activate_task(Lito_task* task)
{
    Lito_TCB* tcb = NULL;
    TCB*       tt = NULL;

    if(task==NULL || task_l==NULL || TCB_l==NULL){return 0;}
  
    // No TCB belongs to this task in TCB_list, so alloc one,
    // fill it and insert into TCb_list and set something.
    if(task->tcb == NULL)
    {
        tcb = (Lito_TCB*)malloc(sizeof(Lito_TCB));
        if(tcb == NULL){return 0;}

        tcb->pid  = task->pid;
        tcb->task = task;
        tcb->tcb  = hardware_TCB_init(function_shell,task);
        TCB_list_insert(tcb);
    }
    else{tcb = task->tcb;}

    tcb->status = RUNNING;

    // Here we should use the scheduling algorithm decides priority.
    tcb->priority = task->priority;

    ///////////////////////////////////////////////////////////////
    ///This is for debugging
    tt = (TCB*)tcb->tcb;
    far_jump(0,tt->selector);
    ///////////////////////////////////////////////////////////////

    // Insert into running queue
    running_queue_insert(tcb);

    return 0;
}

int reset_task(Lito_task* task)
{
    if(task == NULL){return 0;}

    if(task->tcb == NULL){return 0;}

    hardware_TCB_reset((TCB*)task->tcb->tcb,task->function);
    
    return 1;
}

/*
This function is a "shell"(NOT the shell in linux),
It's like a container for the function of job,
and at the end of this "shell function",
the TCB of this job will be reset.
The reason for designing this, 
developer only need to consider how to implement their function, and set the flag correctly,
leave these "reset" things to system.
Parameter:
    A pointor point to a Lito_task structure
Retuen value:
    NO
*/
void function_shell(Lito_task* task)
{
    void (*job)()   = NULL;
    Lito_TCB*   tcb = NULL;

    if(task==NULL || task->function==NULL){return;}

    job = (void (*)())task->function;
    job();
    
    if(task->flag&TG_CLOCK_EVENT)
    {
        // Reset the status of this job
        // Let this job wait the clock event again
        if(!IRQ_trigger_set(CLOCK_IRQ_LINE,task->flag,task)){while(1);}
        reset_task(task);
    }
    else if(task->flag&TG_EXTERNAL_EVENT)
    {
        // Reset the status of this job
        // Let this job wait the external event again
        if(!IRQ_trigger_set(task->extra,task->flag,task)){while(1);}
        reset_task(task);
    }
    else // just a regular job,user just want it run once.
    {
        // Insert some code to exit from TCB list
        // Insert some code to exit from task list
        running_queue_remove(task->pid);

        tcb  = TCB_list_remove(task->pid);
        if(tcb == NULL){while(1);}
        else{free(tcb);}

        task = task_list_remove(task->pid);
        if(task == NULL){while(1);}
        else{free(task);}
    }
    //Here must switch task, otherwise it will be a terrible mitstake 

}
