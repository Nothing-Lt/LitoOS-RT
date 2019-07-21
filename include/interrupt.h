#ifndef INTERRUPT_H
#define INTERRUPT_H

#include <stdint.h>

#include <task.h>

#define MINOR_DEV_NUMBER    25

typedef enum
{
    FLAG_UNUSED   = 0,
    FLAG_FUNCTION = 8,
    FLAG_TASK     = 16,
    FLAG_MESSAGE  = 32
}EVENT_FLAG;

#define WANT_ERR_CODE       1
#define WANT_ERR_IP         2
#define IRQ_SHARED          4

typedef struct
{
    void*    dev;
    EVENT_FLAG flag;
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

int32_t LT_IRQ_trigger_register(uint32_t irq_line,int32_t minor_num,uint32_t flag,Lito_task* task,void* function);

int32_t LT_IRQ_trigger_remove(uint32_t irq_line,int32_t minor_num);

void enable_IRQ();

void disable_IRQ();

void default_handler_hard(uint32_t irq);

#endif