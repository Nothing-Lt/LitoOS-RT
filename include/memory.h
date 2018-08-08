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

#define MIN_BLOCK_SIZE 0x10
#define DIFF(a,b) (unsigned)(&(((a*)0)->b))-(unsigned)(a*)0

typedef struct
{
    unsigned base_add;
    unsigned size;
    void* buff;
}used_block;


typedef struct unused_block
{
    unsigned base_add;
    unsigned size;
    struct unused_block* next;
}unused_block;


/*initial the memory block, this memory block servey for malloc and free function*/
void init_memory_block(unsigned memory_add,unsigned memory_size);

/*this is the "malloc"*/
void* malloc(unsigned size);

/*this is the "free"*/
int free(void* add);


#endif