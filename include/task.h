#ifndef TASK_H
#define TASK_H

#include "../arch/x86/x86.h"
#include "../arch/x86/x86_task.h"

#define MAX_TCB_NUMBER 128
#define MAX_TASK_NUMBER MAX_TCB_NUMBER

/* This structure is for LitoOS,no need to modify */
 typedef struct 
 {
    unsigned pid;
    unsigned flag;      // This task is periodic or aperiodic
    unsigned status;    // running ,waiting, hanging or else
    unsigned priority;  // priority useful for static priority scheduling.
    unsigned WCET;      // Worst Case Execution Time.
    unsigned deadline;  // Releated deadline
    unsigned start_time;// when this task start
    unsigned period;    // what the period of this task
    void*    function;  // Entry point of this task
 }Lito_task;


/*
  This structure is for task control block. 
  When you trying to transplant Lito to other platform.

  ********modify this**********
  Especially for the first element.
*/
typedef struct Lito_TCB
{
    unsigned      pid;
    unsigned      status;         // process status: running, waiting, hanging
    unsigned      compution_time; // rest compution time
    unsigned      priority;       // dynamic priority
    unsigned      deadline;       // Absolute deadline
    void*         tcb;            // When you transplant this system to other platform, modify this!!!!!!!!
    struct Lito_TCB  *next;       // next TCB of process
}Lito_TCB;

/*
Use a queue to manage those tasks,
a task structure represent a task.
*/
typedef struct 
{
    Lito_task* list[MAX_TASK_NUMBER]; //a set of pointer point to task block
    unsigned task_number;
}task_list;

/*
Use a queue to manage the TCB,
a TCB represent a job.
//Here we should know the difference between job and task
*/
typedef struct
{
    Lito_TCB* list[MAX_TCB_NUMBER]; // a set of pointer point to TCB block which assigned by malloc
    unsigned tcb_number;
} TCB_list;

/*Initial the TCB list*/
int TCB_list_init();

/*Initial the task list*/
int task_list_init();

/*Insert new TCB into TCB list*/
int TCB_list_insert(Lito_TCB* tcb);

/*Remove a TCB from TCB list, indexed by pid*/
int TCB_list_remove(unsigned pid);

/*Insert a task into task list*/
int task_list_insert(Lito_task* task);

/*Remove a task from task list,indexed by pid*/
int task_list_remove(unsigned pid);

/*Create new task*/
unsigned create_task(Lito_task *task);

/*Activate task*/
int activate_task(unsigned pid);

#endif