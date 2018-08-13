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
    Lito_task *task;
    disable_IRQ();
    x86_init_hardware();

    init_memory_block(free_memory_add,memory_size-free_memory_add);

    task = (Lito_task*)malloc(sizeof(Lito_task));
    task->pid=++pid;
    task->function = (void*)function;
    task->next = NULL;
    create_task(task);

    while(1);
    enable_IRQ();
}

void function()
{
    int i;

    for(i=0;i<20;);
}