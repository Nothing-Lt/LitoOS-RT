#ifndef MESSAGE_H
#define MESSAGE_H

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
    unsigned src;
    unsigned dst;
    unsigned function;
    unsigned stright_msg;
    unsigned return_value;
    void*    etc;
}MESSAGE;

int send_recv(MESSAGE* msg);

#endif