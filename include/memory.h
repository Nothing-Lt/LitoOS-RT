#ifndef MEMORY_H
#define MEMORY_H
/*
  Memory Model in MYOS
  
  learn how linux alloc memory from heap
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



/*I don't know a real-time system need a page table or not, this is function may be deleted in future*/
unsigned remap_page(void* page_table_add, unsigned linear_add, unsigned physical_add);

/*initial the memory block, this memory block servey for malloc and free function*/
void init_memory_block(void* memory_add,unsigned memory_size);

/*this is the "malloc"*/
void* malloc(unsigned size);

/*this is the "free"*/
int free(void* add);


#endif