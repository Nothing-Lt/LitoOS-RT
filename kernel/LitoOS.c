/*
For adapt this OS to others platform,
implement LT_IRQ_disable,
          LT_IRQ_enable,
          LT_hardware_init,
          hardware_TCB_init
*/

#include <LitoOS.h>

#include <interrupt.h>
#include "../arch/x86/x86.h"

extern unsigned memory_size;
extern unsigned free_memory_add;

void LT_OS_init()
{
    LT_IRQ_disable();        //This function is offered by LitoOS
    LT_hardware_init();  //Hardware initialze 

    init_memory_block(free_memory_add,memory_size-free_memory_add); //LitoOS memory management 
    IRQ_desc_table_init();                                          //LitoOS external IRQ table initialize

    task_list_init();
    TCB_list_init();
    running_queue_init();
}

void LT_OS_start()
{
    //Not finish all yet,
    //so just return here.
    return;

    LT_IRQ_enable();
}