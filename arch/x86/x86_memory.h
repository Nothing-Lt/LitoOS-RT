#ifndef X86_MEMORY_H
#define X86_MEMORY_H

#include "x86_stdint.h"

#define PAGE_EXIST_AUTH   1
#define PAGE_READ_AUTH    0
#define PAGE_WRITE_AUTH   2
#define PAGE_USER_AUTH    4

#define SIZE_OF_PTE       0x1000
#define SIZE_OF_PDE       0x1000
#define SIZE_OF_PAGE      0x1000
#define ELE_NUM_IN_PTE    0x400
#define ELE_NUM_IN_PDE    0x400

#define PAGE_TABLE_ADD    0x300000

#define REFRESH_TLB() asm("movl %cr3,%eax\n\
                           movl %eax,%cr3")

void x86_set_page(uint32_t memory_size);

#endif