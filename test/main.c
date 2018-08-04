#include <interrupt.h>
#include <memory.h>
#include "../arch/x86/x86.h"

int main()
{

	disable_IRQ();
    x86_init_hardware();

    remap_page((unsigned*)PAGE_TABLE_ADD, 0x100000, 0x200000);

	while(1);
}