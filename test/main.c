#include <interrupt.h>
#include <memory.h>
#include "../arch/x86/x86.h"

int main()
{

    disable_IRQ();
    x86_init_hardware();


    while(1);
    enable_IRQ();
}