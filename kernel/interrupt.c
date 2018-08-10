#include <interrupt.h>

// specific platform is x86
#include "../arch/x86/x86.h"
#include "../arch/x86/interrupt/x86_interrupt.h"

IRQ_desc IRQ_desc_table[IRQLINE_NUMBER];

void enable_IRQ()
{
    x86_enable_IRQ();
}

void disable_IRQ()
{
    x86_disable_IRQ();
}

int sys_regist_IRQ(unsigned irq_line,unsigned flag,void* dev,unsigned priority)
{
    return -1;
}

int sys_remove_IRQ(unsigned irq_line,unsigned minor,void* dev)
{
    return -1;
}