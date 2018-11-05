#include <LitoOS.h>

#include <message.h>

extern unsigned pid;

void function();

int main()
{
    Lito_task* task = NULL;

    LT_OS_init();
    
    task = (Lito_task*)malloc(sizeof(Lito_task));
    task->flag     = NORMAL_TASK;
    task->pid      = ++pid;
    task->priority = MAX_PRIORITY-1; 
    task->function = (void*)function;
    task->next     = NULL;
    task->tcb      = NULL;
    LT_create_task(task);

    LT_OS_start();

    while(1);
    LT_IRQ_enable();
}

void function()
{
    int i;
    MESSAGE msg;

    LT_message_send(&msg);

    for(i=0;i<20;);
}