#include <task.h>
#include <memory.h>

#include "../arch/x86/x86.h"
#include "../arch/x86/x86_task.h"

task_list* task_l;
TCB_list* TCB_l;

unsigned pid;

/*
Initial task list 
Parameter:
    void
Return value:
    0: falied(because malloc)
    1: successed
*/
int task_list_init()
{
    int i;

    task_l = (task_list*)malloc(sizeof(task_list));
    if(task_l==NULL)
    {
        return 0;
    }
    
    task_l->task_number=0;
    for(i=0; i<MAX_TASK_NUMBER; i++)
    {
        task_l->list[i]=NULL;
    }

    return 1;
}


/*
initial the TCB list
Parameter:
    void
Return value:
    0: failed (might because some mistake occured in malloc)
    1: succesed
*/
int TCB_list_init()
{
    int i;
    
    TCB_l = (TCB_list*)malloc(sizeof(TCB_list));
    if(TCB_l==NULL)
    {
        return 0;
    }

    TCB_l->tcb_number=0;
    for(i=0; i<MAX_TCB_NUMBER; i++)
    {
        TCB_l->list[i] = NULL;
    }

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

    if(TCB_l==NULL||tcb==NULL)
    {
        return 0;
    }

    if(TCB_l->tcb_number >= MAX_TCB_NUMBER)
    {
        return 0;
    }
    
    for(i=0;i<MAX_TCB_NUMBER;i++)
    {
        if(TCB_l->list[i]==NULL)
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
    0: Failed
    1: Successed
*/
int TCB_list_remove(unsigned pid)
{
    int i;
 
    if(TCB_l==NULL||pid==0)
    {
        return 0;
    }

    for(i=0;i<MAX_TCB_NUMBER;i++)
    {
        if(TCB_l->list[i]!=NULL && TCB_l->list[i]->pid==pid)
        {
            free(TCB_l->list[i]);
            TCB_l->list[i]=NULL;
            TCB_l->tcb_number--;
            return 1;
        }
    }
    return 0;
}

/*
Insert an element into Lito_task list
Parameter:
    a pointer point to an Lito_task instant
Return value:
    0: Failed
    1: Successed
*/
int task_list_insert(Lito_task* task)
{
    int i;

    if(task_l==NULL||task==NULL)
    {
        return 0;
    }

    if(task_l->task_number >= MAX_TASK_NUMBER)
    {
        return 0;
    }

    for(i=0;i<MAX_TASK_NUMBER;i++)
    {
        if(task_l->list[i]==NULL)
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
    0: Failed
    1: Successed
*/
int task_list_remove(unsigned pid)
{
    int i;
    if(task_l==NULL||pid==0)
    {
        return 0;
    }

    for(i=0;i<MAX_TASK_NUMBER;i++)
    {
        if(task_l->list[i]!=NULL && task_l->list[i]->pid==pid)
        {
            free(task_l->list[i]);
            task_l->list[i]=NULL;
            task_l->task_number--;
            return 1;
        }
    }
    return 0;
}

/* 
Parameter:
   Lito_task structure
Return value:
   0      :failed to create new task
   others :Success
*/
unsigned create_task(Lito_task* task)
{
    Lito_TCB *tcb=NULL;

    if(task == NULL)
    {
        return 0;
    }

    task_list_insert(task);


    if(task->flag&TG_CLOCK_EVENT)
    {
        /* those tasks triggered by Clock interruption,
           most for periodtc tasks */
    }
    else if(task->flag&TG_EXTERNAL_EVENT)
    {
        /* Those tasks triggered by External interruption,
           most for aperiodic tasks */
    }
    else if(task->flag&NORMAL_EVENT)
    {
        /*Those normal tasks,just run once, and maybe no deadline*/
        activate_task(task->pid);
    }

    return 1;
}

/*
Activativate specific task
Parameter:
   process id
Return value:
   1: success
   0: otherwise
*/
int activate_task(unsigned pid)
{
    int i;
    Lito_TCB* tcb = NULL;
    Lito_task* lt = NULL;

    if(pid==0 || task_l==NULL || TCB_l==NULL)
    {
        return 0;
    }
  
    /*First, search the task which you want to activate from the TCB list,
      if it not exists in the TCB list,then try to search from task list.*/
    for(i=0;i<MAX_TCB_NUMBER;i++)
    {
        if(TCB_l->list[i]!=NULL)
        {
            if(TCB_l->list[i]->pid==pid)
            {
                TCB_l->list[i]->status = RUNNING;
                // Insert TCB_l[i] into running queue;
                //
                return 1;
            }
        }
    }  
    
    /*Second, we didn't found the task you are trying to activate from the TCB list,
      then try to find this task from task list, and regist it into TCB list,run it.*/
    for(i=0;i<MAX_TASK_NUMBER;i++)
    {
        if(task_l->list[i] != NULL)
        {
            lt=task_l->list[i];
            if(lt->pid == pid)
            {
                tcb = (Lito_TCB*)malloc(sizeof(Lito_TCB));
                if(tcb == NULL)
                {
                    return 0;
                }
                tcb->pid = lt->pid;
                tcb->tcb = set_hardware_TCB(lt->function);
                tcb->status = RUNNING;
                tcb->priority = lt->priority;
                TCB_list_insert(tcb);
                // Insert TCB_l[i] into running queue
                //
                return 1;
            }
        }
    }



    return 0;
}

/*
This function is a "shell",

  
*/
void function_shell(Lito_task* task)
{
    void (*job)() = NULL;

    if(task!=NULL && task->function!=NULL)
    {
        job = (void (*)())task->function;
        job();   
    }
    
    if(task->flag == TG_EXTERNAL_EVENT)
    {
        // Reset the status of this job
        // Let this job wait the external event again
    }
    if(task->flag == TG_CLOCK_EVENT)
    {
        // Reset the status of this job
        // Let this job wait the clock event again
    }
    else
    {  
        /*
         Insert some code to exit from TCB list
         Insert some code to exit from task list
        */
    }

}