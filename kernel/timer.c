#include <timer.h>

#include <stdint.h>
#include <interrupt.h>

uint32_t system_time;

void timer_handler()
{

}

void LT_timer_init()
{
	sys_IRQLINE_set(0x20,timer_handler);
}