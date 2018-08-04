#ifndef MEMORY_H
#define MEMORY_H
/*
  Memory Model in MYOS

                                                                                  
                                                                                  
                   1Gbytes                                                       4Gbytes
0                  0x40000000                                                    0xFFFFFFFF
|-------------------|-------------------------------------------------------------|
|  1Gbytes          |               3Gbytes                                       |
|KERNEL SPACE       |              USER SPACE                                     |
|                   |                                                             |
|-------------------|-------------------------------------------------------------|

*/

typedef struct
{
  unsigned int base;
  unsigned int size;
}memory_room;

unsigned remap_page(void* page_table_add, unsigned linear_add, unsigned physical_add);

void* malloc(unsigned size);

int free(void* add);


#endif