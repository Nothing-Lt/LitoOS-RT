#ifndef TASK_H
#define TASK_H

#include "x86.h"
#include <task.h>


typedef struct
{
    unsigned pretask,esp0,ss0,   esp1,ss1,esp2,ss2;
    unsigned cr3    ,eip, eflags,eax ,ecx,edx, ebx, esp, ebp, esi, edi;
    unsigned es     ,cs,  ss,    ds  ,fs, gs,  ldt, iomap_base;
}tss;

typedef struct 
{
    struct tss tasc;
    unsigned selector,user_esp;
}hardware_task;

#endif