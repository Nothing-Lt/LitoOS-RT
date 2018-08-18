#ifndef TASK_H
#define TASK_H

#define MAX_TCB_NUMBER 128
#define MAX_TASK_NUMBER MAX_TCB_NUMBER

#define TG_CLOCK_EVENT    0x1   //For Periodic JOBs
#define TG_EXTERNAL_EVENT 0x2   //For Aperiodic JOBs
#define NORMAL_TASK       0x4   //For Normal JOBs

#define RUNNING           0x1   //task status
#define READY             0x2   //task status
#define HANGING           0x4   //task status


/* This structure is for LitoOS,no need to modify */
 typedef struct Lito_task
 {
    unsigned          pid;
    unsigned          flag;      // This task is periodic or aperiodic
    unsigned          priority;  // priority useful for static priority scheduling.
    unsigned          WCET;      // Worst Case Execution Time.
    unsigned          deadline;  // Releated deadline
    unsigned          start_time;// when this task start
    unsigned          period;    // what the period of this task
    unsigned          extra;     // External event IRQ line number and something else 
    void*             function;  // Entry point of this task
    struct Lito_TCB*  tcb;       // Point to TCB instance 
    struct Lito_task* next;      // Point to next task, till now, it's used by interrupt handler
 }Lito_task;


/*
  This structure is for task control block. 
  When you trying to transplant Lito to other platform.
*/
typedef struct Lito_TCB
{
    unsigned         pid;  
    unsigned         status;         // process status: running, waiting, hanging
    unsigned         compution_time; // rest compution time
    unsigned         priority;       // dynamic priority,this priority will be decide in running time
    unsigned         deadline;       // Absolute deadline, will be decided in running time
    Lito_task*       task;           // Point to the task instance, 
    void*            tcb;            // When you transplant this system to other platform, modify this!!!!!!!!
    struct Lito_TCB* next;           // next TCB of process
}Lito_TCB;

/*
  This structrue is for running queue,
  those scheduling algorithm implemented in schedule.c,
  would operate on this queue. 
*/
typedef struct
{
}Lito_running_queue;


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

/*Initial the running queue*/
int running_queue_init();

/*Insert new TCB into TCB list*/
int TCB_list_insert(Lito_TCB* tcb);

/*Remove a TCB from TCB list, indexed by pid*/
int TCB_list_remove(unsigned pid);

/*Insert a task into task list*/
int task_list_insert(Lito_task* task);

/*Remove a task from task list,indexed by pid*/
int task_list_remove(unsigned pid);

/*Insert TCB into running queue*/
int running_queue_insert(Lito_TCB* tcb);

/*Remove TCB from running queue*/
int running_queue_remove(unsigned pid);

/*Create new task*/
unsigned create_task(Lito_task* task);

/*Activate task*/
int activate_task(Lito_task* task);

/*Shell funtion for jobs*/
void function_shell(Lito_task* task);

#endif