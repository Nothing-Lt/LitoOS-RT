#include <message.h>

#include <util.h>
#include <task.h>
#include <interrupt.h>

#include "../arch/x86/x86.h"

/*
    Send message by using software interupt,
    'sys_message_function' supported by hardware implementation.
    it should support message send and message receive.
*/
void LT_message_send(MESSAGE* msg)
{
    if(msg == NULL){return;}

    //This fcuntion offered by hardware coder.
    sys_message_function(msg);
}

void LT_message_recv(MESSAGE* msg)
{
    if(msg == NULL){return;}

    //This fucntion offered by hardware coder.
    sys_message_function(msg);
}

int sys_message_send(MESSAGE* msg)
{
    return 0;
}

int sys_message_receive(MESSAGE* msg)
{
    return 0;
}


/*
    Message handler defined for software interrupt handler.
    This function would be regist to IRQ line 0x40,
*/
void sys_message_handler(MESSAGE* msg)
{
    if(msg == NULL){return;}

    switch(msg->type)
    {
        // Trying to send this message.
        case SEND:
        break;
        
        //Try to receive message from someone.
        case RECV:
        break;

        //Trying to send message and give some feedback.
        case ROUND_TRIP:
        break;
        
        default:return;
    }
}

/*
    Initialize message handler,
    regist sys_message_handler function to IRQ line 0x40.
*/
int LT_message_init()
{
    return sys_IRQLINE_set(0x40,sys_message_handler);
}