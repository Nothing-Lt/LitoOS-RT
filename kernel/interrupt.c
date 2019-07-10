/*
    In this file, function for interrupt was defined.

    IRQLINE_NUMBER irq line.
    For each IRQ line, maximum MINOR_DEV_NUMBER minor device is allowed.

    In LitoOS, the way I organize interrupt is:
        1. For each system, it has several IRQ line, each IRQ line has one handler, 
           and each handler is initialized as defualt_handler_hard.
           If developer wants to modify the handler of one IRQ line, he can use sys_IRQLINE_set function. 
           Function sys_IRQLINE_reset function can reset the handler to be the default handler.
        2. For each IRQ line, multiple device might bind with one IRQ line, 
           so I defined a function IRQ_trigger_set() function, 
           developer set a task or fucntion triggered by this calling this function,
           but, if you want to use this function and make sure this works, 
           please don't use sys_IRQLINE_set, because only default check the handler list.
        3. Actually, developer should not touch sys_IRQLINE_set function, this should used only by kernel developer,
           so normal developer should just use LT_IRQ_trigger_set fucntion.

    Function:
        void LT_IRQ_desc_table_init() 
        For initializing the interrupt handler 

        sys_IRQLINE_set
        For setting the handler of IRQ line, 

*/

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
    int32_t i,j;
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
    Set a function to specific IRQ line.
    Return value:
    -1: FAILED
    Otherwise: SUCCESS
*/
int32_t sys_IRQLINE_set(uint32_t irq_line,void* handler)
{
    if(irq_line >= IRQLINE_NUMBER)
    {
        return -1;
    }

    // If success,return IRQ line number.
    if(IRQLINE_handler_set(irq_line,handler))
    {
        return irq_line;
    }

    // Failed
    return -1;
}

/*
    Reset function from specific IRQ line.
    Return value:
    -1: FALIED
    Other: SUCCESS
*/ 
int32_t sys_IRQLINE_reset(uint32_t irq_line)
{
    if(MINOR_DEV_NUMBER <= irq_line)
    {
        return -1;
    }

    if(0x40 == irq_line)
    {
        if(IRQLINE_handler_set(irq_line,default_handler_soft))
        {
            return irq_line;
        }
    }

    if(IRQLINE_handler_set(irq_line,default_handler_hard))
    {
        return irq_line;
    }
    
    return -1;
}

/*
    Regist a device to specific IRQ line
    Return value:
    -1:    FALIED
    Other: SUCCESS
 */
int32_t LT_IRQ_trigger_set(uint32_t irq_line,int32_t minor_num,uint32_t flag,Lito_task* task,void* function)
{
    int32_t minor_idx = 0;

    if(irq_line>=IRQLINE_NUMBER || task==NULL){return -1;}

    // Out of bound
    if(minor_num >= MINOR_DEV_NUMBER)
    {
        return -1;
    }

    // Not available
    if((-1 != minor_num) && (UNUSED != IRQ_desc_table[irq_line].minor_table[minor_num].flag))
    {
        return -1;
    }

    // Corresponding parameter should not be NULL
    if(FUNCTION_FLAG == flag)
    {
        if(NULL == function)
        {
            return -1;
        }
    }
    else if((MESSAGE_FLAG == flag) || (TASK_FLAG == flag))
    {
        if(NULL == task)
        {
            return -1;
        }
    }

    // looking for 
    if(-1 == minor_num)
    {
        for(minor_idx = 0 ; minor_idx < MINOR_DEV_NUMBER ; minor_idx++)
        {
            if(UNUSED == IRQ_desc_table[irq_line].minor_table[minor_idx].flag)
            {
                break;
            }
        }

        minor_num = minor_idx;
    }
    
    // Found a position
    if(MINOR_DEV_NUMBER > minor_num)
    {
        if(FUNCTION_FLAG == flag)
        {
            IRQ_desc_table[irq_line].minor_table[minor_num].dev = (void*)function;
            IRQ_desc_table[irq_line].minor_table[minor_num].flag = FUNCTION_FLAG;
        }
        else if(TASK_FLAG == flag)
        {
            IRQ_desc_table[irq_line].minor_table[minor_num].dev = (void*)task;
            IRQ_desc_table[irq_line].minor_table[minor_num].flag = TASK_FLAG;
        }
        else if(MESSAGE_FLAG == flag)
        {
            IRQ_desc_table[irq_line].minor_table[minor_num].dev = NULL;
            IRQ_desc_table[irq_line].minor_table[minor_num].flag = MESSAGE_FLAG;
            IRQ_desc_table[irq_line].minor_table[minor_num].pid = task->pid;
        }

        return minor_num;
    }

    return -1;
}

/*
    Reset the minor device on irq line 
    -1: FAILED
    Other: SUCCESS
*/
int32_t LT_IRQ_trigger_reset(uint32_t irq_line,int32_t minor_num)
{
    int32_t minor_idx = 0;

    if(IRQLINE_NUMBER <= irq_line)
    {
        return -1;
    }

    if(MINOR_DEV_NUMBER <= minor_num)
    {
        return -1;
    }

    if(-1 == minor_num)
    {
        for(minor_idx = 0 ; minor_idx < MINOR_DEV_NUMBER ; minor_idx++)
        {
            IRQ_desc_table[irq_line].minor_table[minor_idx].flag = UNUSED;            
        }

        return MINOR_DEV_NUMBER;
    }

    IRQ_desc_table[irq_line].minor_table[minor_num].flag = UNUSED;

    return minor_num;
}

void default_handler_hard(uint32_t irq_line)
{
    int32_t minor_idx;
    IRQ_minor_desc* imd = NULL;
    void (*handle_function)() = NULL;
    //Message msg;
    
    // check if this irq is legle 
    if( (irq_line < REUSEABLE_IRQLINE) || (irq_line > IRQLINE_NUMBER) ){return;}
    
    imd = IRQ_desc_table[irq_line].minor_table;
    for(minor_idx = 0 ; minor_idx < MINOR_DEV_NUMBER ; minor_idx++)
    {
        switch(imd[minor_idx].flag)
        {
            case FUNCTION_FLAG:
                handle_function = (void(*)())imd[minor_idx].dev;
                handle_function();
            break;
            case TASK_FLAG:
                LT_activate_task((Lito_task*)imd[minor_idx].dev);
            break;
            case MESSAGE_FLAG:
                // Send message
            break;
            case UNUSED:
            default:
            break;
        }
    }
}