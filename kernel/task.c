/**
 * Task list is common array, size of each array is MAX_TCB_NUMBER,
 * task_insert is just finding for an empty slot and put it at this slot.
 * 
 * Task_remove is function for removing variable of task.
 * 
 * running_queue is linkedlist
 * 
 * For any scheduling algorithm, 
 * reorganize this running queue after new tcb inserted to achieve their goal.
 */

#include <task.h>
#include <memory.h>
#include <schedule.h>
#include <interrupt.h>

#include "../arch/x86/x86.h"
#include "../arch/x86/x86_task.h"
#include "../arch/x86/interrupt/x86_interrupt.h"

Lito_TCB* ready_queue;

static task_list* task_l;

volatile pid_t pid;

extern SCHEDULING_ALGORITHM sa;

void (*initialize)();

int32_t (*insert_OK)(Lito_TCB* tcb1, Lito_TCB* tcb2);

void (*running_queue_reorganize)();

void (*scheduling)(Lito_TCB* tcbs[CPU_NUM],uint32_t* next_call);

void (*job_exit)();

void (*algorithm_exit)();


/*
Initial task list 
Parameter:
    No
Return value:
    0: falied(because malloc)
    1: successed
*/
int32_t LT_task_list_init()
{
    int32_t i;

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
Initialize the running queue
Parameter:
    No
Return value:
    0:failed
    1:Successed
*/
int32_t LT_ready_queue_init()
{
    int32_t i;

    ready_queue = NULL;

    return 1;
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
Lito_task* task_list_remove(pid_t pid)
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

/**
 * Insert tcb to running queue,
 * every time a job insert to running queue, 
 * scheduling algorithm have to reorganize this queue
 * Parameter:
 *     Pointer of Lito_TCB structure
 * Return value:
 *     1: Successed
 *     0: Failed
 */
int32_t ready_queue_insert(Lito_TCB* tcb)
{
    int32_t inserted = 0;
    Lito_TCB** tcb_pp = NULL;
    
    if(NULL == tcb){return 0;}

    for(tcb_pp = &ready_queue ; *tcb_pp ; tcb_pp = &((*tcb_pp)->next))
    {
        // Check wether should I insert tcb to this position.
        if(insert_OK(*tcb_pp,tcb))
        {
            // According to algorithm designed by developer, insert this tcb to this position.
            tcb->next = *tcb_pp;
            *tcb_pp = tcb;
            inserted = 1;
            break;
        }
    }

    if(!inserted)
    {
        *tcb_pp = tcb;
    }

    return 1;
}

/**
 * Insert tcb to running queue,
 * every time a job insert to running queue, 
 * scheduling algorithm have to reorganize this queue
 * Parameter:
 *     Pointer of Lito_TCB structure
 * Return value:
 *     Address of variable of Lito_TCB structure: Successed
 *     NULL: Failed
 */
Lito_TCB* ready_queue_remove(pid_t pid)
{
    Lito_TCB** tcb_pp = NULL;
    Lito_TCB*  result = NULL;
    Lito_task* task_p = NULL;

    for(tcb_pp = &ready_queue ; *tcb_pp ; tcb_pp = &((*tcb_pp)->next))
    {
        task_p = (*tcb_pp)->task;
        if(NULL != task_p)
        {
            if(pid == task_p->pid)
            {
                result = *tcb_pp;
                *tcb_pp = (*tcb_pp)->next;
                break;
            }
        }
    }

    return result;
}

/** 
 * Create task and tcb block according to the information in Lito_task variable.
 * Parameter:
 *   Lito_task structure
 * Return value:
 * 0      :failed to create new task
 * others :Success
 */
uint32_t LT_create_task(Lito_task* task)
{
    if(NULL == task){return 0;}

    task_list_insert(task);

    if(task->flag & TG_CLOCK_EVENT)
    {
        /* those tasks triggered by Clock interruption,
           most for periodtc tasks */
        if(!IRQ_trigger_set(CLOCK_IRQ_LINE,task->flag,task)){while(1);}
    }
    else if(task->flag & TG_EXTERNAL_EVENT)
    {
        /* Those tasks triggered by External interruption,
           most for aperiodic tasks */
        if(!IRQ_trigger_set(task->extra,task->flag,task)){while(1);}
    }
    else if(task->flag & NORMAL_TASK)
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

    if((NULL == task) || (NULL == task_l)){return 0;}
  
    // No TCB belongs to this task in TCB_list, so alloc one,
    // fill it and insert into TCb_list and set something.
    if(NULL == task->tcb)
    {
        tcb = (Lito_TCB*)malloc(sizeof(Lito_TCB));
        if(NULL == tcb){return 0;}

        tcb->task = task;
        tcb->tcb  = hardware_TCB_init(function_shell,task);
        ready_queue_insert(tcb);
    }
    else{tcb = task->tcb;}

    tcb->status = RUNNING;

    // Here we should use the scheduling algorithm decides priority.
    tcb->priority = task->priority;

    ///////////////////////////////////////////////////////////////
    ///This is for debugging
    tt = (TCB*)(tcb->tcb);
    far_jump(0,tt->selector);
    ///////////////////////////////////////////////////////////////

    // Insert into running queue
    ready_queue_insert(tcb);

    return 0;
}

int32_t reset_task(Lito_task* task)
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

    if((NULL == task) || (NULL == task->function)){return;}

    job = (void (*)())(task->function);
    job();
    
    // Following code will be executed after the job finished.
    if((task->flag) & TG_CLOCK_EVENT)
    {
        // Reset the status of this job
        // Let this job wait for the clock event again
        if(!IRQ_trigger_set(CLOCK_IRQ_LINE,task->flag,task)){while(1);}
        reset_task(task);
    }
    else if((task->flag) & TG_EXTERNAL_EVENT)
    {
        // Reset the status of this job
        // Let this job wait for the external event again
        if(!IRQ_trigger_set(task->extra, task->flag, task)){while(1);}
        reset_task(task);
    }
    else // just a regular job,user just want it run once.
    {
        // Insert some code to exit from ready queue
        // Insert some code to exit from task list
        tcb = ready_queue_remove(task->pid);
        if(NULL == tcb){while(1);}
        else{free(tcb);}

        task = task_list_remove(task->pid);
        if(NULL == task){while(1);}
        else{free(task);}
    }
    //Here must switch task, otherwise it will be a terrible mitstake 
}

/*
 Setup scheduling algorithm to LitoOS.
 In my imagenation, this scheduling algorithm is modifiedable.
 So in the future, this part might be changed.
*/
void LT_scheduling_algorithm_setup()
{
    initialize = (void (*)())sa.initialize;
    
    insert_OK  = (int32_t (*)(Lito_TCB*,Lito_TCB*))sa.insert_OK;

    running_queue_reorganize = (void (*)())sa.reorganize;

    scheduling = (void (*)(Lito_TCB* [CPU_NUM],uint32_t* next_call))sa.scheduler;

    job_exit = (void (*)())sa.job_exit;

    algorithm_exit = (void (*)())sa.algorithm_exit;
}