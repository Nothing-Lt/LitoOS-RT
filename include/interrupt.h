#ifndef INTERRUPT_H
#define INTERRUPT_H

#define MAX_DEV_PER_IRQLINE 25
#define UNUSED              0
#define WANT_ERR_CODE       1
#define WANT_ERR_IP         2
#define IRQ_SHARED          4

typedef struct
{
    void*    dev;
    unsigned flag;
    unsigned process_id;
    unsigned priority;
}IRQ_minor_desc;

typedef struct 
{
    IRQ_minor_desc minor_table[MAX_DEV_PER_IRQLINE];
    unsigned registed_number;
}IRQ_desc;

int sys_regist_IRQ(unsigned irq_line,unsigned flag, void* dev,unsigned priority);

int sys_remove_IRQ(unsigned irq_line,unsigned minor,void* dev);

void enable_IRQ();

void disable_IRQ();

#endif