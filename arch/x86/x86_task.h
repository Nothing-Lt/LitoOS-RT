#ifndef X86_TASK_H
#define X86_TASK_H

#include "x86_stdint.h"

typedef struct
{
    uint32_t pretask,esp0,ss0   ,esp1,ss1,esp2,ss2;
    uint32_t cr3    ,eip ,eflags,eax ,ecx,edx ,ebx, esp, ebp, esi, edi;
    uint32_t es     ,cs  ,ss    ,ds  ,fs , gs ,ldt, iomap_base;
}tss;

typedef struct TCB
{
    tss tasc;
    uint32_t selector,user_esp;
}TCB;


void* hardware_TCB_init(void* function,void* parameter);

void hardware_TCB_reset(TCB* tcb,void* parameter);

#endif