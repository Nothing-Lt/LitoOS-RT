
#include "../src/LitoOS/include/task.h"
#include "../src/LitoOS/include/timer.h"
#include "longan_nano.h"
#include "lcd.h"

extern LT_SCHEDULE_STATUS lt_schedule_status;

#define ASM_CONTEXT_SAVE(tcb_save) __asm volatile(\
        "addi sp, sp, -(33*4)  \n"\
        "sw ra, 0(sp)    \n"\
        "sw x3, 1*4(sp)  \n"\
        "sw x4, 2*4(sp)  \n"\
        "sw x5, 3*4(sp)  \n"\
        "sw x6, 4*4(sp)  \n"\
        "sw x7, 5*4(sp)  \n"\
        "sw x8, 6*4(sp)  \n"\
        "sw x9, 7*4(sp)  \n"\
        "sw x10, 8*4(sp) \n"\
        "sw x11, 9*4(sp)\n"\
        "sw x12, 10*4(sp)\n"\
        "sw x13, 11*4(sp)\n"\
        "sw x14, 12*4(sp)\n"\
        "sw x15, 13*4(sp)\n"\
        "sw x16, 14*4(sp)\n"\
        "sw x17, 15*4(sp)\n"\
        "sw x18, 16*4(sp)\n"\
        "sw x19, 17*4(sp)\n"\
        "sw x20, 18*4(sp)\n"\
        "sw x21, 19*4(sp)\n"\
        "sw x22, 20*4(sp)\n"\
        "sw x23, 21*4(sp)\n"\
        "sw x24, 22*4(sp)\n"\
        "sw x25, 23*4(sp)\n"\
        "sw x26, 24*4(sp)\n"\
        "sw x27, 25*4(sp)\n"\
        "sw x28, 26*4(sp)\n"\
        "sw x29, 27*4(sp)\n"\
        "sw x30, 28*4(sp)\n"\
        "sw x31, 29*4(sp)\n"\
        "csrr t0, mstatus\n"\
        "sw t0, 30*4(sp) \n"\
        "csrr t0,mcause\n"\
        "sw t0,31*4(sp)\n"\
        "csrr t0,mepc\n"\
        "sw t0,32*4(sp)\n"\
        "sw sp, 0(%[_tcb_save])\n"\
        ::[_tcb_save] "r" (tcb_save)\
)

#define ASM_CONTEXT_RESTORE(tcb_load) __asm volatile(\
        "lw sp, 0(%[_tcb_load])\n"\
        "lw t0,32*4(sp)\n"\
        "lw t1, 31*4(sp) \n"\
        "srli t1,t1,31\n"\
        "bne t1,x0,set_mepc\n"\
        "addi t0,t0,4\n"\
        "set_mepc:\n"\
        "csrw mepc, t0 \n"\
        "lw t0,30*4(sp)\n"\
        "csrw mstatus, t0\n"\
        "lw x31, 29*4(sp)\n"\
        "lw x30, 28*4(sp)\n"\
        "lw x29, 27*4(sp)\n"\
        "lw x28, 26*4(sp)\n"\
        "lw x27, 25*4(sp)\n"\
        "lw x26, 24*4(sp)\n"\
        "lw x25, 23*4(sp)\n"\
        "lw x24, 22*4(sp)\n"\
        "lw x23, 21*4(sp)\n"\
        "lw x22, 20*4(sp)\n"\
        "lw x21, 19*4(sp)\n"\
        "lw x20, 18*4(sp)\n"\
        "lw x19, 17*4(sp)\n"\
        "lw x18, 16*4(sp)\n"\
        "lw x17, 15*4(sp)\n"\
        "lw x16, 14*4(sp)\n"\
        "lw x15, 13*4(sp)\n"\
        "lw x14, 12*4(sp)\n"\
        "lw x13, 11*4(sp)\n"\
        "lw x12, 10*4(sp)\n"\
        "lw x11, 9*4(sp)\n"\
        "lw x10, 8*4(sp) \n"\
        "lw x9, 7*4(sp)  \n"\
        "lw x8, 6*4(sp)  \n"\
        "lw x7, 5*4(sp)  \n"\
        "lw x6, 4*4(sp)  \n"\
        "lw x5, 3*4(sp)  \n"\
        "lw x4, 2*4(sp)  \n"\
        "lw x3, 1*4(sp)  \n"\
        "lw x1, 0(sp)\n"\
        "addi sp, sp, 33*4\n"\
        ::[_tcb_load] "r" (tcb_load):\
)

#define LONGAN_NANO_CPU_CLOCK_HZ 108000000
#define LONGAN_NANO_TICK_RATE_HZ 250
#define LONGAN_NANO_CLINT_BASE_ADDRESS 0xd2000000
#define LONGAN_NANO_SYSTICK_LOW_ADDRESS (LONGAN_NANO_CLINT_BASE_ADDRESS + 0xBFF8)
#define LONGAN_NANO_SYSTICK_HIGH_ADDRESS (LONGAN_NANO_CLINT_BASE_ADDRESS + 0xBFFC)
#define LONGAN_NANO_COMPARE_TIMER_REGISTER (LONGAN_NANO_CLINT_BASE_ADDRESS + 0x4000)

extern TCB_t* tcb_running;
extern LT_TCB_item_t* tcb_item_running_task;
extern LT_timer_event_list_t* timer_event_list;

uint32_t tick;

void TIMER1_Init(void)
{
    tick = 0;
    eclic_global_interrupt_enable();//使能全局中断
    eclic_set_nlbits(ECLIC_GROUP_LEVEL3_PRIO1);//分组
    eclic_irq_enable(TIMER1_IRQn, 1 ,0);//使能TIMER1中断请求,设置优先级
 
    rcu_periph_clock_enable(RCU_TIMER1);//使能TIMER1时钟
    timer_deinit(TIMER1);//重置TIMER1
    timer_parameter_struct timer1;//定义结构体
    timer1.prescaler = 107;//预装载值
    timer1.alignedmode = TIMER_COUNTER_EDGE;//边沿对齐模式
    timer1.counterdirection = TIMER_COUNTER_UP;//向上计数
    timer1.period = 9999;//周期
    timer1.clockdivision = TIMER_CKDIV_DIV1;//时钟分频
    timer1.repetitioncounter = 0;//重复值，一般赋值为0
    timer_init(TIMER1, &timer1);//初始化TIMER01 
    timer_interrupt_enable(TIMER1, TIMER_INT_UP);//启用TIMER1中断
    timer_enable(TIMER1);//使能TIMER1
}

void hardware_init()
{
    TIMER1_Init();
    Lcd_Init();			// init OLED
    LCD_Clear(WHITE);
    BACK_COLOR=WHITE;
}

void hardware_tick_inc()
{
    tick++;
}

uint32_t hardware_tick_get()
{
    return tick;
}

void lr_temp()
{
	while(1){
	}
}

void hardware_TCB_init(TCB_t*tcb, void* function, void* parameter, void* stack_pointer, size_t stack_size)
{
    uint32_t mstatus = 0;
 
    // Setup the hardware context
    CONTENT_t* tcb_in_stack = NULL;
    register uint32_t tp __asm("x3");

    if((NULL == tcb) || (NULL == function) || (NULL == stack_pointer)){
        return;
    }

    tcb_in_stack = (CONTENT_t*)(((uint32_t)stack_pointer) + stack_size - sizeof(CONTENT_t));
    tcb->stack_pointer = tcb_in_stack;

    // Check it is in machine mode or user mode.
    __asm volatile(
        "csrrsi %[result],mstatus,0 \n":
        [result] "=r" (mstatus)::);

    tcb_in_stack->mepc = (uint32_t)function;
    tcb_in_stack->x1 = (uint32_t)lr_temp;
    tcb_in_stack->x3 = 0;
    tcb_in_stack->x4 = tp;
    tcb_in_stack->mstatus = mstatus | 0x1880;
    tcb_in_stack->x10 = (uint32_t)parameter;
    tcb_in_stack->mcause = 0x80000000;

    tcb_in_stack->x5  = 5;
    tcb_in_stack->x6  = 6;
    tcb_in_stack->x7  = 7;
    tcb_in_stack->x8  = 8;
    tcb_in_stack->x9  = tcb_in_stack->x10 = tcb_in_stack->x11 = tcb_in_stack->x12 = \
    tcb_in_stack->x13 = tcb_in_stack->x14 = tcb_in_stack->x15 = tcb_in_stack->x16 = \
    tcb_in_stack->x17 = tcb_in_stack->x18 = tcb_in_stack->x19 = tcb_in_stack->x20 = \
    tcb_in_stack->x21 = tcb_in_stack->x22 = tcb_in_stack->x23 = tcb_in_stack->x24 = \
    tcb_in_stack->x25 = tcb_in_stack->x26 = tcb_in_stack->x27 = tcb_in_stack->x28 = \
    tcb_in_stack->x29 = tcb_in_stack->x30 = tcb_in_stack->x31 = 0;
}

void __attribute__((naked)) trap_entry()
{
    register uint32_t mcause __asm("t0");
    __asm volatile(".align 8");
    ASM_CONTEXT_SAVE(tcb_running);

    // handler code
    __asm volatile("csrr t0,mcause"::);
    if(0x80000000 & mcause){
        // since the interrupt
        mcause &= 0x7fffffff;
        switch(mcause)
        {
            case 0:
            break;
        }
    }
    else{
        // since the exception or system call
        mcause &= 0x7fffffff;
        switch(mcause)
        {
            case 0:
            case 1:
            default:
                LT_tcb_item_running_task_update();
            break;
        }
    }

    ASM_CONTEXT_RESTORE(tcb_running);
    __asm volatile("mret");
}

void LT_IRQ_enable()
{
    __asm volatile(
        "csrrsi t0, mstatus, 8 \n"
    );
}

void LT_IRQ_disable()
{
    __asm volatile(
        "csrrci t0, mstatus, 8 \n"
    );
}

void LT_dummy_task()
{
    uint32_t addr = 0;

    while(1){
        __asm volatile(
            "csrrc %[result],mtvec,x0\n":
            [result] "=r" (addr)::);
        
		LT_task_switch();
    }
}

void LT_first_task_start()
{
    __asm volatile( "csrs mie, %0" :: "r"(0x880) );  
    __asm(
        "lw sp, 0(%[_tcb_load])\n"
        "lw t0, 31*4(sp) \n"
        "csrrw  t0, mstatus, t0\n"
        "lw t0, 32*4(sp) \n"
        "csrw   mepc,t0\n"
        "lw x31, 30*4(sp)\n"
        "lw x30, 29*4(sp)\n"
        "lw x29, 28*4(sp)\n"
        "lw x28, 27*4(sp)\n"
        "lw x27, 26*4(sp)\n"
        "lw x26, 25*4(sp)\n"
        "lw x25, 24*4(sp)\n"
        "lw x24, 23*4(sp)\n"
        "lw x23, 22*4(sp)\n"
        "lw x22, 21*4(sp)\n"
        "lw x21, 20*4(sp)\n"
        "lw x20, 19*4(sp)\n"
        "lw x19, 18*4(sp)\n"
        "lw x18, 17*4(sp)\n"
        "lw x17, 16*4(sp)\n"
        "lw x16, 15*4(sp)\n"
        "lw x15, 14*4(sp)\n"
        "lw x14, 13*4(sp)\n"
        "lw x13, 12*4(sp)\n"
        "lw x12, 11*4(sp)\n"
        "lw x11, 10*4(sp)\n"
        "lw x10, 9*4(sp) \n"
        "lw x9, 8*4(sp)  \n"
        "lw x8, 7*4(sp)  \n"
        "lw x7, 6*4(sp)  \n"
        "lw x6, 5*4(sp)  \n"
        "lw x5, 4*4(sp)  \n"
        "lw x4, 3*4(sp)  \n"
        "lw x3, 2*4(sp)  \n"
        "lw ra, 32*4(sp) \n"
        "addi sp, sp, 33*4\n"
        "ret"
        ::[_tcb_load] "r" (tcb_running));
}

 
void TIMER1_IRQHandler(void)
 {
    uint32_t current_tick = 0;
	LT_SCHEDULE_FLAG_t ask_for_scheduling = NO_SCHEDULING;
	LT_SCHEDULE_FLAG_t will_schedule = NO_SCHEDULING;
	LT_timer_event_t* timer_event = NULL;
	LT_timer_event_item_t* timer_event_item = NULL;
	LT_timer_event_item_t* timer_event_item_free = NULL;

    if(SET == timer_interrupt_flag_get(TIMER1, TIMER_INT_FLAG_UP))//判断是否产生中断
    {
        hardware_tick_inc();
	    current_tick = hardware_tick_get();

	    // Check the timer event.
	    if((NULL != timer_event_list) && (0 != timer_event_list->length)){
	    	timer_event_item = timer_event_list->head;
	    	while(timer_event_item){
	    		timer_event = (LT_timer_event_t*)timer_event_item->content;
	    		if((NULL != timer_event) && (current_tick >= timer_event->issue_at)){
	    			if(LT_TIMER_EVENT_FUNCTION & timer_event->flag){
	    				(timer_event->handler)();
	    			}
	    			else if(LT_TIMER_EVENT_SEMAPHORE & timer_event->flag){
	    				LT_semaphore_put_from_ISR(timer_event->semaphore_queue,LT_QUEUE_FLAG_FROM_IRQ,&ask_for_scheduling);
	    				will_schedule |= ask_for_scheduling;
	    			}

	    			// This event already been issued, so remove it from timer event list.
	    			timer_event_item_free = timer_event_item;
	    			timer_event_item = timer_event_item->next;
	    			LT_list_remove(timer_event_list,timer_event_item_free);
	    			free(timer_event_item_free);
	    			timer_event_item_free = NULL;
	    		}
	    		else{
	    			timer_event_item = timer_event_item->next;
	    		}
	    	}
	    }

        timer_interrupt_flag_clear(TIMER1, TIMER_INT_FLAG_UP);//清除中断标志位

	    // The scheduling is not started yet
        if(LT_SCHEDULE_RUNNING != lt_schedule_status){
            return;
        }

	    if(ASK_FOR_SCHEDULING & will_schedule){
	    	LT_task_switch();
	    }
    }
 }