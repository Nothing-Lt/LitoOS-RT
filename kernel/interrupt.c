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
    Lito_task* task     = NULL;
    Lito_task* tmp      = NULL;
    //Message msg;
	
	// check if this irq is legle 
    if( irq<REUSEABLE_IRQLINE || irq>IRQLINE_NUMBER )
    {
    	return;
    }
    
    // Activate those tasks which are waitting this interrupt.
    // Those tasks waked up is triggered by external event.
    // For each IRQ line, the first minor descriptor (minor_table[0]) is for Keeping the task structure,
    // for those tasks request for this external event
    imd = &(IRQ_desc_table[irq].minor_table[0]);
    if(imd->flag!=UNUSED)
    {
        if(imd->flag & TG_EXTERNAL_EVENT)
        {
            task = (Lito_task*)(imd->dev);
        }

        // This while loop is for waking up those tasks waitting for this external event
        while(task!=NULL)
        {
            activate_task(task);
            tmp  = task;
            task = task->next;
            tmp->next = NULL;
        }
    }

    // Some tasks need this external interrupt
    // send those tasks message by using IPC
    if( IRQ_desc_table[irq].registed_number!=0)
    {
        for( i=1 ; i<IRQ_desc_table[irq].registed_number ; i++ )
        {
        	imd = &(IRQ_desc_table[irq].minor_table[i]);
            if(imd->flag!=UNUSED)
            {
                //Message something
            }
        }
    }
    return;
}