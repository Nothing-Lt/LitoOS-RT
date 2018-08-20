#include <interrupt.h>
#include <memory.h>
#include <task.h>
#include "../arch/x86/x86.h"

extern unsigned memory_size;
extern unsigned free_memory_add;

extern unsigned pid;

void function();

int main()
{
    Lito_task* task;
    disable_IRQ();        //This function is offered by LitoOS
    x86_init_hardware();  //Hardware initialze 

    init_memory_block(free_memory_add,memory_size-free_memory_add); //LitoOS memory management 
    IRQ_desc_table_init();                                          //LitoOS external IRQ table initialize

    task_list_init();
    TCB_list_init();
    running_queue_init();
    
    task = (Lito_task*)malloc(sizeof(Lito_task));
    task->flag = NORMAL_TASK;
    task->pid=++pid;
    task->function = (void*)function;
    task->next = NULL;
    task->tcb = NULL;
    create_task(task);

    while(1);
    enable_IRQ();
}

void function()
{
    int i;

    for(i=0;i<20;);
}