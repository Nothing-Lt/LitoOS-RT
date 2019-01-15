#include <interrupt.h>

#include <task.h>


// specific platform is x86
#include "../arch/x86/x86.h"
#include "../arch/x86/interrupt/x86_interrupt.h"

IRQ_desc IRQ_desc_table[IRQLINE_NUMBER];

/*
    Initialize the IRQ describe table.
*/
void LT_IRQ_desc_table_init()
{
    int i,j;
    IRQ_minor_desc* minor_desc = NULL;

    for(i=0;i<IRQLINE_NUMBER;i++)
    {
        IRQ_desc_table[i].registed_number = 0;
        for(j=0;j<MINOR_DEV_NUMBER;j++)
        {
            minor_desc           = &(IRQ_desc_table[i].minor_table[j]);
            minor_desc->dev      = NULL;
            minor_desc->flag     = UNUSED;
            minor_desc->pid      = \
            minor_desc->priority = 0;
        }
    }
}

/*
    Regist a device to specific IRQ line.
    Return value:
    -1: FAILED
    Otherwise: SUCCESS
*/
int sys_IRQLINE_regist(unsigned irq_line,unsigned flag,void* dev,unsigned priority)
{
    if(irq_line >= IRQLINE_NUMBER){return -1;}

    // Special case for software interrupt handler.
    if(irq_line == 0x40)
    {
        // If success,return IRQ line number.
        if(IRQLINE_handler_set(irq_line,dev)){return irq_line;}
    }
    else
    {
        //I didn't figured out what will happened here.
    }

    // Failed
    return -1;
}

int sys_IRQLINE_remove(unsigned irq_line,unsigned minor,void* dev)
{
    return -1;
}

int IRQ_trigger_set(unsigned irq_line,unsigned flag,Lito_task* task)
{
    if(irq_line>=IRQLINE_NUMBER || task==NULL){return 0;}

    task->next = (Lito_task*)(IRQ_desc_table[irq_line].minor_table[0].dev);
    IRQ_desc_table[irq_line].minor_table[0].dev = (void*)task;
    IRQ_desc_table[irq_line].minor_table[0].flag = task->flag;

    return 1;
}

void default_handler_hard(unsigned irq)
{
    int i;
    IRQ_minor_desc* imd = NULL;
    Lito_task*      task= NULL;
    Lito_task*      tmp = NULL;
    //Message msg;
    
    // check if this irq is legle 
    if( (irq < REUSEABLE_IRQLINE) || (irq > IRQLINE_NUMBER) ){return;}
    
    // Activate those tasks which are waitting for this interrupt.
    // Those tasks waked up is triggered by external event.
    // For each IRQ line, the first minor descriptor (minor_table[0]) is for Keeping the task structure,
    // for those tasks request for this external event
    imd = &(IRQ_desc_table[irq].minor_table[0]);
    if(imd->flag != UNUSED)
    {
        if(imd->flag & TG_EXTERNAL_EVENT)
        {
            task = (Lito_task*)(imd->dev);
        }

        // This while loop is for waking up those tasks waitting for this external event
        while(task != NULL)
        {
            LT_activate_task(task);
            tmp       = task;
            task      = task->next;
            tmp->next = NULL;
        }
    }

    // Some tasks need this external interrupt
    // send those tasks message by using IPC
    if(IRQ_desc_table[irq].registed_number != 0)
    {
        for( i=1 ; i<MINOR_DEV_NUMBER ; i++ )
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