#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

typedef enum
{
    SEND      ,
    RECV      ,
    ROUND_TRIP,
    WAIT_SEND ,
    WAIT_RECV ,
    ANY
}MESSAGE_TYPE;

#define MSG_BUF_SIZE  128
#define INTERRUPT     0x9100

typedef struct 
{
    MESSAGE_TYPE type;
    uint32_t src;
    uint32_t dst;
    uint32_t function;
    uint32_t stright_msg;


    uint32_t return_value;
    void*    etc;
}MESSAGE;

void LT_message_send(MESSAGE* msg);

void LT_message_recv(MESSAGE* msg);

int LT_message_init();

#endif