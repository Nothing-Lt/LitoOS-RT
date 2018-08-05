#ifndef TASK_H
#define TASK_H

#include "../arch/x86/x86_task.h"


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
    unsigned      status;        // process status: running, waiting, hanging
    unsigned      compution_time;// rest compution time
    unsigned      priority;      // dynamic priority
    unsigned      deadline;      // Absolute deadline
    hardware_task tcb;           // When you transplant this system to other platform, modify this!!!!!!!!
    Lito_TCB      *next;         // next TCB of process
}Lito_TCB;

/*Create new task*/
unsigned create_task(Lito_task *task);

/*Activate task*/
int activate_task(unsigned pid);


#endif