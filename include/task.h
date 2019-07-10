#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#include <message.h>

#define MAX_PRIORITY      128
#define MIN_PRIORITY      1
#define MAX_TCB_NUMBER    128
#define MAX_TASK_NUMBER   MAX_TCB_NUMBER

#define TG_CLOCK_EVENT    0x1   //For Periodic JOBs
#define TG_EXTERNAL_EVENT 0x2   //For Aperiodic JOBs
#define NORMAL_TASK       0x4   //For Normal JOBs

#define RUNNING           0x1   //task status
#define READY             0x2   //task status
#define HANGING           0x4   //task status

typedef uint32_t pid_t;

/* This structure is for LitoOS,no need to modify */
 typedef struct Lito_task
 {
    pid_t             pid;
    uint32_t          flag;      // This task is periodic or aperiodic
    uint32_t          priority;  // priority useful for static priority scheduling.
    uint32_t          WCET;      // Worst Case Execution Time.
    uint32_t          deadline;  // Releated deadline
    uint32_t          start_time;// when this task start
    uint32_t          period;    // what the period of this task
    uint32_t          extra;     // External event IRQ line number and something else 
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
    uint32_t         status;         // process status: running, waiting, hanging
    uint32_t         rect;           // rest execution time
    uint32_t         priority;       // dynamic priority,this priority will be decide in running time
    uint32_t         deadline;       // Absolute deadline, will be decided in running time
    MESSAGE*         msg;
    Lito_task*       task;           // Point to the task instance, 
    void*            tcb;            // When you adapt this system to other platform, modify this!!!!!!!!
    struct Lito_TCB* prev; 
    struct Lito_TCB* next;           // next TCB of process
}Lito_TCB;

/*
  Use a queue to manage those tasks,
  a task structure represent a task.
*/
typedef struct 
{
    Lito_task* list[MAX_TASK_NUMBER]; //a set of pointer point to task block
    uint32_t task_number;
}task_list;

/*Initialize the task list*/
int LT_task_list_init();

/*Initialize ready queue*/
int32_t LT_ready_queue_init();

/*Insert a task into task list*/
int task_list_insert(Lito_task* task);

/*Remove a task from task list,indexed by pid*/
Lito_task* task_list_remove(uint32_t pid);

/*Insert TCB into running queue*/
int ready_queue_insert(Lito_TCB* tcb);

/*Remove TCB from running queue*/
Lito_TCB* ready_queue_remove(uint32_t pid);

/*Create new task*/
uint32_t LT_create_task(Lito_task* task);

/*Activate task*/
int LT_activate_task(Lito_task* task);

/*Setup the scheduling algorithm for LitoOS*/
void LT_scheduling_algorithm_setup();

/*Shell funtion for jobs*/
void function_shell(Lito_task* task);

/*Activate scheduling*/
void scheduling_activate();

#endif