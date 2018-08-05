#ifndef MESSAGE_H
#define MESSAGE_H

#define SEND          0x1
#define RECV          0x2
#define ROUND_TRIP    0x3
#define WAIT_SEND     0x4
#define WAIT_RECV     0x5
#define ANY           0x6
#define MSG_BUF_SIZE  128
#define INTERRUPT     0x9100

typedef struct 
{
    unsigned type;
    unsigned src;
    unsigned dst;
    unsigned function;
    unsigned stright_msg;
    unsigned return_value;
    void*    etc;
}message;

typedef struct 
{
    message msg_buf[MSG_BUF_SIZE];
    unsigned count;
}message_management;


int send_recv(message* msg);


#endif