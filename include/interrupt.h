#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

#include <task.h>

#define MINOR_DEV_NUMBER    25

#define UNUSED              0
#define FUNCTION_FLAG       8
#define TASK_FLAG           16
#define MESSAGE_FLAG        32

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

int32_t sys_IRQLINE_set(uint32_t irq_line,void* handler);

int32_t sys_IRQLINE_reset(uint32_t irq_line);

int32_t LT_IRQ_trigger_set(uint32_t irq_line,int32_t minor_num,uint32_t flag,Lito_task* task,void* function);

int32_t LT_IRQ_trigger_reset(uint32_t irq_line,int32_t minor_num);

void enable_IRQ();

void disable_IRQ();

void default_handler_hard(uint32_t irq);

#endif