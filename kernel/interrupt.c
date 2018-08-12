#include <interrupt.h>

#include <task.h>


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

void default_handler_hard(unsigned irq)
{
    int i;
    IRQ_minor_desc* imd = NULL;
    //Message msg;
	
	// check if this irq is legle 
    if( irq<REUSEABLE_IRQLINE || irq>IRQLINE_NUMBER )
    {
    	return;
    }
    
    // check this some driver registed this IRQ line
    if( IRQ_desc_table[irq].registed_number!=0)
    {
        for( i=0 ; i<IRQ_desc_table[irq].registed_number ; i++ )
        {
        	imd = &(IRQ_desc_table[irq].minor_table[i]);
            if(imd->flag!=UNUSED)
            {
                if(imd->flag & TG_EXTERNAL_EVENT)
                {
                	activate_task(imd->pid);
                }   
            }
        }
    }
    return;
}