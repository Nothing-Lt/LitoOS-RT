/*
For adapt this OS to others platform,
implement LT_IRQ_disable,
          LT_IRQ_enable,
          LT_hardware_init,
          hardware_TCB_init
*/

#include <LitoOS.h>

#include <interrupt.h>
#include <message.h>

#include "../arch/x86/x86.h"

extern unsigned memory_size;
extern unsigned free_memory_add;

void LT_OS_init()
{
    LT_IRQ_disable();        //This function is offered by LitoOS
    
    LT_hardware_init();  //Hardware initialze 

    LT_memory_block_init(free_memory_add,memory_size-free_memory_add); //LitoOS memory management 
    
    LT_IRQ_desc_table_init();                                          //LitoOS external IRQ table initialize

    LT_task_list_init();
    
    LT_TCB_list_init();
    
    LT_running_queue_init();

    LT_message_init();
}

void LT_OS_start()
{
    //Not finish all yet,
    //so just return here.
    return;

    LT_IRQ_enable();
}