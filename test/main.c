#include <LitoOS.h>

extern unsigned pid;

void function()
{
    int i;

    for(i=0;i<20;);
}

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
    create_task(task);

    LT_OS_start();

    while(1);
    LT_IRQ_enable();
}
