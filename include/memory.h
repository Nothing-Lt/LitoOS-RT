#ifndef MEMORY_H
#define MEMORY_H

/*
  Memory Model in LitoOS
  
  learn how linux alloc memory from heap

  Here I will use the most simple model to manage the memory,
  this means there are no page table in this system.
  Because in real-time system, the most important is time,
  but the complex memory management model will be time consuming.

*/

#include <stdint.h>

#define MIN_BLOCK_SIZE 0x10
#define DIFF(a,b) (uint32_t)(&(((a*)0)->b))-0

typedef struct
{
    uint32_t base_add;
    uint32_t size;
    void*    buff;
}used_block;


typedef struct unused_block
{
    uint32_t base_add;
    uint32_t size;
    struct   unused_block* next;
}unused_block;


/*initial the memory block, this memory block servey for malloc and free function*/
void LT_memory_block_init(uint32_t memory_add,uint32_t memory_size);

/*this is the "malloc"*/
void* malloc(size_t size);

/*this is the "free"*/
int32_t free(void* add);


#endif