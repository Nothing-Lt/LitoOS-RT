#include "x86_interrupt.h"

#include "../x86.h"
#include "../x86_stdint.h"

//#include <IPC/message.h>
#include <interrupt.h>

//this extened from kernel/interrupt.c
//extern IRQ_desc IRQ_desc_table[IRQLINE_NUMBER];

// this only used on x86 platform
handle_list handler_list;


// default software interrupt exception handler
// some of exception with error code and ip address
// so in some handler, should ses arg1 as error_ip and arg2 as error_code
// this is only in x86 architure
void default_handler_soft(uint32_t error_ip,uint32_t error_code)
{
    return;
}

// set the handler for No.irq line handler
// this function only for system, not for user program
int IRQLINE_handler_set(uint32_t irq,void* function)
{
    // out of range of IRQ handler table
    if(irq>=IRQLINE_NUMBER){return 0;}
    
    // NULL pointer is not allowed
    if(function==NULL){return 0;}

    handler_list.function_pointer[irq]=function;

    return 1;
}

// remove and set the default handler to No.irq line
// this function only for system, not for user program
int IRQLINE_handler_remove(uint32_t irq)
{
    if(irq>=IRQLINE_NUMBER)       // out of range of IRQ handler table
    {
        return 0;
    }

    if(irq<0x20)                   //0-0x1f belongs to interrupt or exception caussed by software
    {
        handler_list.function_pointer[irq]=(void*)default_handler_soft; 
    }
    else                           //0x20-0xff belongs to interrupt caused by hardware
    {
        handler_list.function_pointer[irq]=(void*)default_handler_hard;
    }
    
    return 1;
}

// set default handler for each IRQ line, 
// this function must be called when initial the x86 hardware by system
void init_handler_for_IRQLINE()
{
    int i;
    
    for( i=SOFT_IRQLINE_BEGIN ; i<=SOFT_IRQLINE_END ; i++ )
    {
        handler_list.function_pointer[i]=(void*)default_handler_soft;
    }
    for( i=HARD_IRQLINE_BEGIN ; i<=HARD_IRQLINE_END ; i++ )
    {
        //Here default_handler_hard was defined in kernel/interrupt.c
        handler_list.function_pointer[i]=(void*)default_handler_hard;
    }
}




// following procedure is hanler function


void handle0x00(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x00]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x00];
        handler(error_ip,error_code);
    }
}

void handle0x01(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x01]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x01];
        handler(error_ip,error_code);
    }
}


void handle0x02(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x02]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x02];
        handler(error_ip,error_code);
    }
}

void handle0x03(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x03]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x03];
        handler(error_ip,error_code);
    }
}

void handle0x04(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x04]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x04];
        handler(error_ip,error_code);
    }
}


void handle0x05(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x05]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x05];
        handler(error_ip,error_code);
    }
}

void handle0x06(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x06]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x06];
        handler(error_ip,error_code);
    }
}

void handle0x07(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x07]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x07];
        handler(error_ip,error_code);
    }
}

void handle0x08(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x08]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x08];
        handler(error_ip,error_code);
    }
}

void handle0x09(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x09]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x09];
        handler(error_ip,error_code);
    }
}

void handle0x0a(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x0a]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x0a];
        handler(error_ip,error_code);
    }
}

void handle0x0b(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x0b]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x0b];
        handler(error_ip,error_code);
    }
}

void handle0x0c(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x0c]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x0c];
        handler(error_ip,error_code);
    }
}

void handle0x0d(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x0d]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x0d];
        handler(error_ip,error_code);
    }
}

void handle0x0e(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x0e]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x0e];
        handler(error_ip,error_code);
    }
}

void handle0x0f(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x0f]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x0f];
        handler(error_ip,error_code);
    }
}

void handle0x10(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x10]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x10];
        handler(error_ip,error_code);
    }
}

void handle0x11(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x11]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x11];
        handler(error_ip,error_code);
    }
}

void handle0x12(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x12]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x12];
        handler(error_ip,error_code);
    }
}

void handle0x13(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x13]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x13];
        handler(error_ip,error_code);
    }
}

void handle0x14(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x14]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x14];
        handler(error_ip,error_code);
    }
}

void handle0x15(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x15]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x15];
        handler(error_ip,error_code);
    }
}

void handle0x16(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x16]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x16];
        handler(error_ip,error_code);
    }
}

void handle0x17(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x17]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x17];
        handler(error_ip,error_code);
    }
}

void handle0x18(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x18]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x18];
        handler(error_ip,error_code);
    }
}

void handle0x19(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x19]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x19];
        handler(error_ip,error_code);
    }
}


void handle0x1a(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x1a]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x1a];
        handler(error_ip,error_code);
    }
}


void handle0x1b(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x1b]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x1b];
        handler(error_ip,error_code);
    }
}

void handle0x1c(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x1c]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x1c];
        handler(error_ip,error_code);
    }
}

void handle0x1d(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x1d]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x1d];
        handler(error_ip,error_code);
    }
}

void handle0x1e(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x1e]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x1e];
        handler(error_ip,error_code);
    }
}

void handle0x1f(uint32_t error_ip,uint32_t error_code)
{
    void (*handler)(uint32_t error_ip,uint32_t error_code);
    
    if(handler_list.function_pointer[0x1f]!=NULL)
    {
        handler=(void (*)(uint32_t,uint32_t))handler_list.function_pointer[0x1f];
        handler(error_ip,error_code);
    }
}

// these handler for hardware interrupt
void handle0x20()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x20]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x20];
        handler(0x20);
    }

    out_8bits(0x20,0x20);
}

void handle0x21()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x21]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x21];
        handler(0x21);
    }

    out_8bits(0x20,0x20);
}

void handle0x22()
{    
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x22]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x22];
        handler(0x22);
    }

    out_8bits(0x20,0x20);
}

void handle0x23()
{    
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x23]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x23];
        handler(0x23);
    }

    out_8bits(0x20,0x20);
}

void handle0x24()
{    
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x24]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x24];
        handler(0x24);
    }

    out_8bits(0x20,0x20);
}


void handle0x25()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x25]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x25];
        handler(0x25);
    }

    out_8bits(0x20,0x20);
}

void handle0x26()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x26]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x26];
        handler(0x26);
    }

    out_8bits(0x20,0x20);
}

void handle0x27()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x27]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x27];
        handler(0x27);
    }

    out_8bits(0x20,0x20);
}

void handle0x28()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x28]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x28];
        handler(0x28);
    }

    out_8bits(0x20,0x20);
}

void handle0x29()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x29]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x29];
        handler(0x29);
    }

    out_8bits(0x20,0x20);
}

void handle0x2a()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x2a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x2a];
        handler(0x2a);
    }

    out_8bits(0x20,0x20);
}

void handle0x2b()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x2b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x2b];
        handler(0x2b);
    }

    out_8bits(0x20,0x20);
}


void handle0x2c()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x2c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x2c];
        handler(0x2c);
    }

    out_8bits(0x20,0x20);
}
void handle0x2d()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x2d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x2d];
        handler(0x2d);
    }

    out_8bits(0x20,0x20);
}

void handle0x2e()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x2e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x2e];
        handler(0x2e);
    }

    out_8bits(0x20,0x20);
}

void handle0x2f()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x2f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x2f];
        handler(0x2f);
    }

    out_8bits(0x20,0x20);
}

void handle0x30()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x30]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x30];
        handler(0x30);
    }

    out_8bits(0x20,0x20);
}

void handle0x31()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x31]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x31];
        handler(0x31);
    }

    out_8bits(0x20,0x20);
}

void handle0x32()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x32]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x32];
        handler(0x32);
    }

    out_8bits(0x20,0x20);
}

void handle0x33()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x33]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x33];
        handler(0x33);
    }

    out_8bits(0x20,0x20);
}

void handle0x34()
{
    void (*handler)(uint32_t irq);
    
    if(handler_list.function_pointer[0x34]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x34];
        handler(0x34);
    }

    out_8bits(0x20,0x20);
}

void handle0x35()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x35]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x35];
        handler(0x35);
    }

    out_8bits(0x20,0x20);
}

void handle0x36()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x36]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x36];
        handler(0x36);
    }

    out_8bits(0x20,0x20);
}

void handle0x37()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x37]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x37];
        handler(0x37);
    }

    out_8bits(0x20,0x20);
}

void handle0x38()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x38]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x38];
        handler(0x38);
    }

    out_8bits(0x20,0x20);
}

void handle0x39()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x39]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x39];
        handler(0x39);
    }

    out_8bits(0x20,0x20);
}

void handle0x3a()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x3a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x3a];
        handler(0x3a);
    }

    out_8bits(0x20,0x20);
}

void handle0x3b()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x3b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x3b];
        handler(0x3b);
    }

    out_8bits(0x20,0x20);
}

void handle0x3c()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x3c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x3c];
        handler(0x3c);
    }

    out_8bits(0x20,0x20);
}

void handle0x3d()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x3d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x3d];
        handler(0x3d);
    }

    out_8bits(0x20,0x20);
}

void handle0x3e()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x3e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x3e];
        handler(0x3e);
    }

    out_8bits(0x20,0x20);
}

void handle0x3f()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x3f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x3f];
        handler(0x3f);
    }

    out_8bits(0x20,0x20);
}
/*
  int40 was used as software interrupt,
  I use this IRQ to dispatch message(implement IPC mechanism).
  In OS implementation, regist message send and receive function 
  to IRQ 0x40 is OK.
*/
void sys_send_recv(void* msg)
{
    void (*handler)(void*);

    if(handler_list.function_pointer[0x40]!=NULL)
    {
        handler=(void (*)(void*))handler_list.function_pointer[0x40];
        handler(msg);
    } 
} 

void handle0x40()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x40]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x40];
        handler(0x40);
    }

    out_8bits(0x20,0x20);
}

void handle0x41()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x41]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x41];
        handler(0x41);
    }

    out_8bits(0x20,0x20);
}

void handle0x42()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x42]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x42];
        handler(0x42);
    }

    out_8bits(0x20,0x20);
}

void handle0x43()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x43]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x43];
        handler(0x43);
    }

    out_8bits(0x20,0x20);
}

void handle0x44()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x44]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x44];
        handler(0x44);
    }

    out_8bits(0x20,0x20);
}

void handle0x45()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x45]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x45];
        handler(0x45);
    }

    out_8bits(0x20,0x20);
}

void handle0x46()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x46]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x46];
        handler(0x46);
    }

    out_8bits(0x20,0x20);
}

void handle0x47()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x47]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x47];
        handler(0x47);
    }

    out_8bits(0x20,0x20);
}

void handle0x48()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x48]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x48];
        handler(0x48);
    }

    out_8bits(0x20,0x20);
}

void handle0x49()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x49]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x49];
        handler(0x49);
    }

    out_8bits(0x20,0x20);
}

void handle0x4a()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x4a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x4a];
        handler(0x4a);
    }

    out_8bits(0x20,0x20);
}

void handle0x4b()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x4b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x4b];
        handler(0x4b);
    }

    out_8bits(0x20,0x20);
}

void handle0x4c()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x4c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x4c];
        handler(0x4c);
    }

    out_8bits(0x20,0x20);
}

void handle0x4d()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x4d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x4d];
        handler(0x4d);
    }

    out_8bits(0x20,0x20);
}

void handle0x4e()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x4e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x4e];
        handler(0x4e);
    }

    out_8bits(0x20,0x20);
}

void handle0x4f()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x4f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x4f];
        handler(0x4f);
    }

    out_8bits(0x20,0x20);
}

void handle0x50()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x50]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x50];
        handler(0x50);
    }

    out_8bits(0x20,0x20);
}

void handle0x51()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x51]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x51];
        handler(0x51);
    }

    out_8bits(0x20,0x20);
}

void handle0x52()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x52]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x52];
        handler(0x52);
    }

    out_8bits(0x20,0x20);
}

void handle0x53()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x53]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x53];
        handler(0x53);
    }

    out_8bits(0x20,0x20);
}

void handle0x54()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x54]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x54];
        handler(0x54);
    }

    out_8bits(0x20,0x20);
}

void handle0x55()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x55]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x55];
        handler(0x55);
    }

    out_8bits(0x20,0x20);
}

void handle0x56()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x56]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x56];
        handler(0x56);
    }

    out_8bits(0x20,0x20);
}

void handle0x57()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x57]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x57];
        handler(0x57);
    }

    out_8bits(0x20,0x20);
}

void handle0x58()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x58]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x58];
        handler(0x58);
    }

    out_8bits(0x20,0x20);
}

void handle0x59()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x59]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x59];
        handler(0x59);
    }

    out_8bits(0x20,0x20);
}

void handle0x5a()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x5a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x5a];
        handler(0x5a);
    }

    out_8bits(0x20,0x20);
}

void handle0x5b()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x5b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x5b];
        handler(0x5b);
    }

    out_8bits(0x20,0x20);
}

void handle0x5c()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x5c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x5c];
        handler(0x5c);
    }

    out_8bits(0x20,0x20);
}

void handle0x5d()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x5d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x5d];
        handler(0x5d);
    }

    out_8bits(0x20,0x20);
}

void handle0x5e()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x5e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x5e];
        handler(0x5e);
    }

    out_8bits(0x20,0x20);
}

void handle0x5f()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x5f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x5f];
        handler(0x5f);
    }

    out_8bits(0x20,0x20);
}

void handle0x60()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x60]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x60];
        handler(0x60);
    }

    out_8bits(0x20,0x20);
}

void handle0x61()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x61]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x61];
        handler(0x61);
    }

    out_8bits(0x20,0x20);
}

void handle0x62()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x62]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x62];
        handler(0x62);
    }

    out_8bits(0x20,0x20);
}

void handle0x63()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x63]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x63];
        handler(0x63);
    }

    out_8bits(0x20,0x20);
}

void handle0x64()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x64]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x64];
        handler(0x64);
    }

    out_8bits(0x20,0x20);
}

void handle0x65()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x65]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x65];
        handler(0x65);
    }

    out_8bits(0x20,0x20);
}

void handle0x66()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x66]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x66];
        handler(0x66);
    }

    out_8bits(0x20,0x20);
}

void handle0x67()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x67]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x67];
        handler(0x67);
    }

    out_8bits(0x20,0x20);
}

void handle0x68()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x68]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x68];
        handler(0x68);
    }

    out_8bits(0x20,0x20);
}

void handle0x69()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x69]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x69];
        handler(0x69);
    }

    out_8bits(0x20,0x20);
}

void handle0x6a()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x6a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x6a];
        handler(0x6a);
    }

    out_8bits(0x20,0x20);
}

void handle0x6b()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x6b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x6b];
        handler(0x6b);
    }

    out_8bits(0x20,0x20);
}

void handle0x6c()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x6c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x6c];
        handler(0x6c);
    }

    out_8bits(0x20,0x20);
}

void handle0x6d()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x6d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x6d];
        handler(0x6d);
    }

    out_8bits(0x20,0x20);
}

void handle0x6e()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x6e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x6e];
        handler(0x6e);
    }

    out_8bits(0x20,0x20);
}

void handle0x6f()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x6f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x6f];
        handler(0x6f);
    }

    out_8bits(0x20,0x20);
}

void handle0x70()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x70]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x70];
        handler(0x70);
    }

    out_8bits(0x20,0x20);
}

void handle0x71()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x71]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x71];
        handler(0x71);
    }

    out_8bits(0x20,0x20);
}

void handle0x72()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x72]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x72];
        handler(0x72);
    }

    out_8bits(0x20,0x20);
}

void handle0x73()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x73]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x73];
        handler(0x73);
    }

    out_8bits(0x20,0x20);
}

void handle0x74()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x74]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x74];
        handler(0x74);
    }

    out_8bits(0x20,0x20);
}

void handle0x75()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x75]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x75];
        handler(0x75);
    }

    out_8bits(0x20,0x20);
}

void handle0x76()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x76]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x76];
        handler(0x76);
    }

    out_8bits(0x20,0x20);
}

void handle0x77()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x77]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x77];
        handler(0x77);
    }

    out_8bits(0x20,0x20);
}

void handle0x78()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x78]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x78];
        handler(0x78);
    }

    out_8bits(0x20,0x20);
}

void handle0x79()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x79]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x79];
        handler(0x79);
    }

    out_8bits(0x20,0x20);
}

void handle0x7a()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x7a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x7a];
        handler(0x7a);
    }

    out_8bits(0x20,0x20);
}

void handle0x7b()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x7b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x7b];
        handler(0x7b);
    }

    out_8bits(0x20,0x20);
}

void handle0x7c()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x7c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x7c];
        handler(0x7c);
    }

    out_8bits(0x20,0x20);
}

void handle0x7d()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x7d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x7d];
        handler(0x7d);
    }

    out_8bits(0x20,0x20);
}

void handle0x7e()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x7e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x7e];
        handler(0x7e);
    }

    out_8bits(0x20,0x20);
}

void handle0x7f()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x7f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x7f];
        handler(0x7f);
    }

    out_8bits(0x20,0x20);
}

void handle0x80()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x80]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x80];
        handler(0x80);
    }

    out_8bits(0x20,0x20);
}

void handle0x81()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x81]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x81];
        handler(0x81);
    }

    out_8bits(0x20,0x20);
}

void handle0x82()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x82]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x82];
        handler(0x82);
    }

    out_8bits(0x20,0x20);
}

void handle0x83()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x83]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x83];
        handler(0x83);
    }

    out_8bits(0x20,0x20);
}

void handle0x84()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x84]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x84];
        handler(0x84);
    }

    out_8bits(0x20,0x20);
}

void handle0x85()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x85]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x85];
        handler(0x85);
    }

    out_8bits(0x20,0x20);
}

void handle0x86()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x86]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x86];
        handler(0x86);
    }

    out_8bits(0x20,0x20);
}

void handle0x87()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x87]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x87];
        handler(0x87);
    }

    out_8bits(0x20,0x20);
}

void handle0x88()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x88]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x88];
        handler(0x88);
    }

    out_8bits(0x20,0x20);
}

void handle0x89()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x89]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x89];
        handler(0x89);
    }

    out_8bits(0x20,0x20);
}

void handle0x8a()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x8a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x8a];
        handler(0x8a);
    }

    out_8bits(0x20,0x20);
}

void handle0x8b()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x8b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x8b];
        handler(0x8b);
    }

    out_8bits(0x20,0x20);
}

void handle0x8c()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x8c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x8c];
        handler(0x8c);
    }

    out_8bits(0x20,0x20);
}

void handle0x8d()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x8d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x8d];
        handler(0x8d);
    }

    out_8bits(0x20,0x20);
}

void handle0x8e()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x8e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x8e];
        handler(0x8e);
    }

    out_8bits(0x20,0x20);
}

void handle0x8f()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x8f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x8f];
        handler(0x8f);
    }

    out_8bits(0x20,0x20);
}

void handle0x90()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x90]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x90];
        handler(0x90);
    }

    out_8bits(0x20,0x20);
}

void handle0x91()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x91]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x91];
        handler(0x91);
    }

    out_8bits(0x20,0x20);
}

void handle0x92()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x92]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x92];
        handler(0x92);
    }

    out_8bits(0x20,0x20);
}

void handle0x93()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x93]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x93];
        handler(0x93);
    }

    out_8bits(0x20,0x20);
}

void handle0x94()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x94]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x94];
        handler(0x94);
    }

    out_8bits(0x20,0x20);
}

void handle0x95()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x95]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x95];
        handler(0x95);
    }

    out_8bits(0x20,0x20);
}

void handle0x96()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x96]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x96];
        handler(0x96);
    }

    out_8bits(0x20,0x20);
}

void handle0x97()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x97]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x97];
        handler(0x97);
    }

    out_8bits(0x20,0x20);
}

void handle0x98()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x98]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x98];
        handler(0x98);
    }

    out_8bits(0x20,0x20);
}

void handle0x99()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x99]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x99];
        handler(0x99);
    }

    out_8bits(0x20,0x20);
}

void handle0x9a()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x9a]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x9a];
        handler(0x9a);
    }

    out_8bits(0x20,0x20);
}

void handle0x9b()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x9b]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x9b];
        handler(0x9b);
    }

    out_8bits(0x20,0x20);
}

void handle0x9c()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x9c]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x9c];
        handler(0x9c);
    }

    out_8bits(0x20,0x20);
}

void handle0x9d()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x9d]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x9d];
        handler(0x9d);
    }

    out_8bits(0x20,0x20);
}

void handle0x9e()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x9e]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x9e];
        handler(0x9e);
    }

    out_8bits(0x20,0x20);
}

void handle0x9f()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0x9f]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0x9f];
        handler(0x9f);
    }

    out_8bits(0x20,0x20);
}

void handle0xa0()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa0]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa0];
        handler(0xa0);
    }

    out_8bits(0x20,0x20);
}

void handle0xa1()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa1]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa1];
        handler(0xa1);
    }

    out_8bits(0x20,0x20);
}

void handle0xa2()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa2]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa2];
        handler(0xa2);
    }

    out_8bits(0x20,0x20);
}

void handle0xa3()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa3]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa3];
        handler(0xa3);
    }

    out_8bits(0x20,0x20);
}

void handle0xa4()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa4]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa4];
        handler(0xa4);
    }

    out_8bits(0x20,0x20);
}

void handle0xa5()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa5]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa5];
        handler(0xa5);
    }

    out_8bits(0x20,0x20);
}

void handle0xa6()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa6]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa6];
        handler(0xa6);
    }

    out_8bits(0x20,0x20);
}

void handle0xa7()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa7]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa7];
        handler(0xa7);
    }

    out_8bits(0x20,0x20);
}

void handle0xa8()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa8]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa8];
        handler(0xa8);
    }

    out_8bits(0x20,0x20);
}

void handle0xa9()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xa9]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xa9];
        handler(0xa9);
    }

    out_8bits(0x20,0x20);
}

void handle0xaa()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xaa]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xaa];
        handler(0xaa);
    }

    out_8bits(0x20,0x20);
}

void handle0xab()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xab]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xab];
        handler(0xab);
    }

    out_8bits(0x20,0x20);
}

void handle0xac()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xac]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xac];
        handler(0xac);
    }

    out_8bits(0x20,0x20);
}

void handle0xad()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xad]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xad];
        handler(0xad);
    }

    out_8bits(0x20,0x20);
}

void handle0xae()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xae]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xae];
        handler(0xae);
    }

    out_8bits(0x20,0x20);
}

void handle0xaf()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xaf]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xaf];
        handler(0xaf);
    }

    out_8bits(0x20,0x20);
}

void handle0xb0()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb0]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb0];
        handler(0xb0);
    }

    out_8bits(0x20,0x20);
}

void handle0xb1()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb1]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb1];
        handler(0xb1);
    }

    out_8bits(0x20,0x20);
}

void handle0xb2()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb2]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb2];
        handler(0xb2);
    }

    out_8bits(0x20,0x20);
}

void handle0xb3()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb3]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb3];
        handler(0xb3);
    }

    out_8bits(0x20,0x20);
}

void handle0xb4()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb4]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb4];
        handler(0xb4);
    }

    out_8bits(0x20,0x20);
}

void handle0xb5()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb5]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb5];
        handler(0xb5);
    }

    out_8bits(0x20,0x20);
}

void handle0xb6()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb6]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb6];
        handler(0xb6);
    }

    out_8bits(0x20,0x20);
}

void handle0xb7()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb7]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb7];
        handler(0xb7);
    }

    out_8bits(0x20,0x20);
}

void handle0xb8()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb8]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb8];
        handler(0xb8);
    }

    out_8bits(0x20,0x20);
}

void handle0xb9()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xb9]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xb9];
        handler(0xb9);
    }

    out_8bits(0x20,0x20);
}

void handle0xba()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xba]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xba];
        handler(0xba);
    }

    out_8bits(0x20,0x20);
}

void handle0xbb()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xbb]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xbb];
        handler(0xbb);
    }

    out_8bits(0x20,0x20);
}

void handle0xbc()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xbc]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xbc];
        handler(0xbc);
    }

    out_8bits(0x20,0x20);
}

void handle0xbd()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xbd]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xbd];
        handler(0xbd);
    }

    out_8bits(0x20,0x20);
}

void handle0xbe()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xbe]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xbe];
        handler(0xbe);
    }

    out_8bits(0x20,0x20);
}

void handle0xbf()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xbf]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xbf];
        handler(0xbf);
    }

    out_8bits(0x20,0x20);
}

void handle0xc0()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc0]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc0];
        handler(0xc0);
    }

    out_8bits(0x20,0x20);
}

void handle0xc1()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc1]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc1];
        handler(0xc1);
    }

    out_8bits(0x20,0x20);
}

void handle0xc2()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc2]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc2];
        handler(0xc2);
    }

    out_8bits(0x20,0x20);
}

void handle0xc3()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc3]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc3];
        handler(0xc3);
    }

    out_8bits(0x20,0x20);
}

void handle0xc4()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc4]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc4];
        handler(0xc4);
    }

    out_8bits(0x20,0x20);
}

void handle0xc5()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc5]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc5];
        handler(0xc5);
    }

    out_8bits(0x20,0x20);
}

void handle0xc6()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc6]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc6];
        handler(0xc6);
    }

    out_8bits(0x20,0x20);
}

void handle0xc7()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc7]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc7];
        handler(0xc7);
    }

    out_8bits(0x20,0x20);
}

void handle0xc8()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc8]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc8];
        handler(0xc8);
    }

    out_8bits(0x20,0x20);
}

void handle0xc9()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xc9]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xc9];
        handler(0xc9);
    }

    out_8bits(0x20,0x20);
}

void handle0xca()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xca]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xca];
        handler(0xca);
    }

    out_8bits(0x20,0x20);
}

void handle0xcb()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xcb]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xcb];
        handler(0xcb);
    }

    out_8bits(0x20,0x20);
}

void handle0xcc()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xcc]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xcc];
        handler(0xcc);
    }

    out_8bits(0x20,0x20);
}

void handle0xcd()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xcd]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xcd];
        handler(0xcd);
    }

    out_8bits(0x20,0x20);
}

void handle0xce()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xce]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xce];
        handler(0xce);
    }

    out_8bits(0x20,0x20);
}

void handle0xcf()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xcf]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xcf];
        handler(0xcf);
    }

    out_8bits(0x20,0x20);
}

void handle0xd0()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd0]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd0];
        handler(0xd0);
    }

    out_8bits(0x20,0x20);
}

void handle0xd1()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd1]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd1];
        handler(0xd1);
    }

    out_8bits(0x20,0x20);
}

void handle0xd2()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd2]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd2];
        handler(0xd2);
    }

    out_8bits(0x20,0x20);
}

void handle0xd3()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd3]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd3];
        handler(0xd3);
    }

    out_8bits(0x20,0x20);
}

void handle0xd4()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd4]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd4];
        handler(0xd4);
    }

    out_8bits(0x20,0x20);
}

void handle0xd5()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd5]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd5];
        handler(0xd5);
    }

    out_8bits(0x20,0x20);
}

void handle0xd6()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd6]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd6];
        handler(0xd6);
    }

    out_8bits(0x20,0x20);
}

void handle0xd7()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd7]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd7];
        handler(0xd7);
    }

    out_8bits(0x20,0x20);
}

void handle0xd8()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd8]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd8];
        handler(0xd8);
    }

    out_8bits(0x20,0x20);
}

void handle0xd9()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xd9]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xd9];
        handler(0xd9);
    }

    out_8bits(0x20,0x20);
}

void handle0xda()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xda]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xda];
        handler(0xda);
    }

    out_8bits(0x20,0x20);
}

void handle0xdb()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xdb]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xdb];
        handler(0xdb);
    }

    out_8bits(0x20,0x20);
}

void handle0xdc()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xdc]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xdc];
        handler(0xdc);
    }

    out_8bits(0x20,0x20);
}

void handle0xdd()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xdd]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xdd];
        handler(0xdd);
    }

    out_8bits(0x20,0x20);
}

void handle0xde()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xde]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xde];
        handler(0xde);
    }

    out_8bits(0x20,0x20);
}

void handle0xdf()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xdf]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xdf];
        handler(0xdf);
    }

    out_8bits(0x20,0x20);
}

void handle0xe0()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe0]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe0];
        handler(0xe0);
    }

    out_8bits(0x20,0x20);
}

void handle0xe1()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe1]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe1];
        handler(0xe1);
    }

    out_8bits(0x20,0x20);
}

void handle0xe2()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe2]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe2];
        handler(0xe2);
    }

    out_8bits(0x20,0x20);
}

void handle0xe3()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe3]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe3];
        handler(0xe3);
    }

    out_8bits(0x20,0x20);
}

void handle0xe4()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe4]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe4];
        handler(0xe4);
    }

    out_8bits(0x20,0x20);
}

void handle0xe5()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe5]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe5];
        handler(0xe5);
    }

    out_8bits(0x20,0x20);
}

void handle0xe6()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe6]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe6];
        handler(0xe6);
    }

    out_8bits(0x20,0x20);
}

void handle0xe7()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe7]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe7];
        handler(0xe7);
    }

    out_8bits(0x20,0x20);
}

void handle0xe8()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe8]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe8];
        handler(0xe8);
    }

    out_8bits(0x20,0x20);
}

void handle0xe9()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xe9]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xe9];
        handler(0xe9);
    }

    out_8bits(0x20,0x20);
}

void handle0xea()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xea]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xea];
        handler(0xea);
    }

    out_8bits(0x20,0x20);
}

void handle0xeb()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xeb]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xeb];
        handler(0xeb);
    }

    out_8bits(0x20,0x20);
}

void handle0xec()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xec]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xec];
        handler(0xec);
    }

    out_8bits(0x20,0x20);
}

void handle0xed()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xed]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xed];
        handler(0xed);
    }

    out_8bits(0x20,0x20);
}

void handle0xee()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xee]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xee];
        handler(0xee);
    }

    out_8bits(0x20,0x20);
}

void handle0xef()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xef]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xef];
        handler(0xef);
    }

    out_8bits(0x20,0x20);
}

void handle0xf0()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf0]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf0];
        handler(0xf0);
    }

    out_8bits(0x20,0x20);
}

void handle0xf1()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf1]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf1];
        handler(0xf1);
    }

    out_8bits(0x20,0x20);
}

void handle0xf2()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf2]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf2];
        handler(0xf2);
    }

    out_8bits(0x20,0x20);
}

void handle0xf3()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf3]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf3];
        handler(0xf3);
    }

    out_8bits(0x20,0x20);
}

void handle0xf4()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf4]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf4];
        handler(0xf4);
    }

    out_8bits(0x20,0x20);
}

void handle0xf5()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf5]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf5];
        handler(0xf5);
    }

    out_8bits(0x20,0x20);
}

void handle0xf6()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf6]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf6];
        handler(0xf6);
    }

    out_8bits(0x20,0x20);
}

void handle0xf7()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf7]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf7];
        handler(0xf7);
    }

    out_8bits(0x20,0x20);
}

void handle0xf8()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf8]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf8];
        handler(0xf8);
    }

    out_8bits(0x20,0x20);
}

void handle0xf9()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xf9]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xf9];
        handler(0xf9);
    }

    out_8bits(0x20,0x20);
}

void handle0xfa()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xfa]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xfa];
        handler(0xfa);
    }

    out_8bits(0x20,0x20);
}

void handle0xfb()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xfb]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xfb];
        handler(0xfb);
    }

    out_8bits(0x20,0x20);
}

void handle0xfc()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xfc]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xfc];
        handler(0xfc);
    }

    out_8bits(0x20,0x20);
}

void handle0xfd()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xfd]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xfd];
        handler(0xfd);
    }

    out_8bits(0x20,0x20);
}

void handle0xfe()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xfe]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xfe];
        handler(0xfe);
    }

    out_8bits(0x20,0x20);
}

void handle0xff()
{
    void (*handler)(uint32_t irq);

    if(handler_list.function_pointer[0xff]!=NULL)
    {
        handler=(void (*)(uint32_t))handler_list.function_pointer[0xff];
        handler(0xff);
    }

    out_8bits(0x20,0x20);
}
