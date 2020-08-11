#ifndef LONGAN_NANO_H_
#define LONGAN_NANO_H_

#include <sys/types.h>

typedef enum {
    LONGAN_NANO_MACHINE_MODE_MASK = 0x1800,
}LONGAN_NANO_MASK;

typedef struct{
    uint32_t x1, x3, x4, x5, x6, x7, x8, x9, x10;
    uint32_t x11,x12,x13,x14,x15,x16,x17,x18,x19,x20;
    uint32_t x21,x22,x23,x24,x25,x26,x27,x28,x29,x30;
    uint32_t x31,mstatus,mcause,mepc;
}CONTENT_t;


typedef struct{
    CONTENT_t* stack_pointer;
}TCB_t;

#define hardware_context_switch() __asm volatile("ecall"::)

void hardware_init();

void hardware_tick_inc();

uint32_t hardware_tick_get();

void hardware_timer_interrupt_set();

void hardware_TCB_init(TCB_t* tcb, void* function, void* parameter, void* stack_pointer, size_t size);

void LT_IRQ_enable();

void LT_IRQ_disable();

void LT_dummy_task();

void LT_first_task_start();

#endif