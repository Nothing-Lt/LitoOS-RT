#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

#include <task.h>

#define MINOR_DEV_NUMBER    25
#define UNUSED              0
#define WANT_ERR_CODE       1
#define WANT_ERR_IP         2
#define IRQ_SHARED          4

typedef struct
{
    void*    dev;
    uint32_t flag;
    uint32_t pid;
    uint32_t priority;
}IRQ_minor_desc;

typedef struct 
{
    IRQ_minor_desc minor_table[MINOR_DEV_NUMBER];
    uint32_t registed_number;
}IRQ_desc;

void LT_IRQ_desc_table_init();

int32_t sys_IRQLINE_regist(uint32_t irq_line,uint32_t flag, void* dev,uint32_t priority);

int32_t sys_IRQLINE_remove(uint32_t irq_line,uint32_t minor,void* dev);

int32_t IRQ_trigger_set(uint32_t irq_line,uint32_t flag,Lito_task* task);

void enable_IRQ();

void disable_IRQ();

void default_handler_hard(uint32_t irq);

#endif