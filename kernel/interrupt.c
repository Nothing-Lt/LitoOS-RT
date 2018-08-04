#include <interrupt.h>

// specific platform is x86
#include"../arch/x86/interrupt/"

IRQ_desc IRQ_desc_table[IRQLINE_NUMBER];

int sys_regist_IRQ(unsigned irq_line,unsigned flag,void* dev,unsigned priority)
{

    return -1;
}

int sys_remove_IRQ(unsigned irq_line,unsigned minorvoid* dev)
{
    return -1;
}