#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <task.h>

#define MINOR_DEV_NUMBER    25
#define UNUSED              0
#define WANT_ERR_CODE       1
#define WANT_ERR_IP         2
#define IRQ_SHARED          4

typedef struct
{
    void*    dev;
    unsigned flag;
    unsigned pid;
    unsigned priority;
}IRQ_minor_desc;

typedef struct 
{
    IRQ_minor_desc minor_table[MINOR_DEV_NUMBER];
    unsigned registed_number;
}IRQ_desc;

void LT_IRQ_desc_table_init();

int sys_IRQLINE_regist(unsigned irq_line,unsigned flag, void* dev,unsigned priority);

int sys_IRQLINE_remove(unsigned irq_line,unsigned minor,void* dev);

int IRQ_trigger_set(unsigned irq_line,unsigned flag,Lito_task* task);

void enable_IRQ();

void disable_IRQ();

void default_handler_hard(unsigned irq);

#endif