
#include "x86.h"
#include "x86_task.h"
#include "x86_memory.h"

#include <memory.h>

extern gdt* gdt_addr;

void* hardware_TCB_init(void* function,void* parameter)
{
    TCB* tcb = NULL;
    void* esp = NULL;
    unsigned gdt_selector=0;

    if(function==NULL)
    {
        return NULL;
    }

    esp = malloc(2*SIZE_OF_PAGE);
    if(esp==NULL)
    {
        return NULL;
    }
    
    tcb = malloc(sizeof(TCB));
    if(tcb == NULL)
    {
        return NULL;
    }

    gdt_selector = find_empty_gdt();
    if(gdt_selector == 0)
    {
        return NULL;
    }
    
    tcb->tasc.cr3 = PAGE_TABLE_ADD;
    tcb->tasc.eip = (unsigned)function;
    tcb->tasc.eflags = KERNEL_EFLAG;
    
    tcb->tasc.eax = tcb->tasc.ecx = tcb->tasc.edx = \
    tcb->tasc.ebx = tcb->tasc.edi = 0;
    tcb->tasc.ebp = (unsigned)esp;
    tcb->tasc.esp = (unsigned)esp + 2*SIZE_OF_PAGE;
    
    tcb->tasc.es = tcb->tasc.ds = tcb->tasc.fs = \
    tcb->tasc.gs = tcb->tasc.ss = DS_GDT<<3;
    tcb->tasc.cs = CS_GDT<<3;

    tcb->tasc.iomap_base = NORMAL_IOMAPBASE;

    tcb->selector = gdt_selector<<3;
    set_gdt(&gdt_addr[gdt_selector],(unsigned)&(tcb->tasc),TSS_SIZE,TSS_DESCRIB);

    *((void**)(esp+2*SIZE_OF_PAGE-sizeof(void*))) = parameter;

    return (void*)tcb;
}