#include <memory.h>
#include <util.h>

#include "../arch/x86/x86_memory.h"

unsigned kernel_size;
unsigned memory_size;
unsigned free_memory_add;

unused_block* unused_block_list;


void init_memory_block(void* memory_add, unsigned memory_size)
{
    unused_block_list           = (unused_block*)memory_add;
    unused_block_list->base_add = (unsigned)memory_add;
    unused_block_list->size     = memory_size;
    unused_block_list->next     = NULL;
}



void* malloc(unsigned size)
{
    unsigned alloc_size      =0;
    unsigned fixed_base_add  =0;
    unsigned fixed_size      =0;
    used_block* allocated_mem=NULL;
    unused_block* new_block  =NULL;
    unused_block* temp       =NULL;

    if(size==0)
    {
    	return NULL;
    }

    alloc_size = ((size/MIN_BLOCK_SIZE)+1)*MIN_BLOCK_SIZE;
    alloc_size += DIFF(used_block,buff);

    temp = unused_block_list;
    for(; temp!=NULL && temp->next!=NULL; temp=temp->next)
    {
        if(temp->next->size >= alloc_size)
        {
        	allocated_mem = (used_block*)temp->next;
            
            fixed_base_add = temp->next->base_add + alloc_size;
            fixed_size = temp->next->size - alloc_size;

            new_block = (unused_block*)fixed_base_add;
            new_block->base_add = fixed_base_add;
            new_block->size = fixed_size;
            new_block->next = temp->next->next;
            
            temp->next = new_block;

        }
    }
    
    if(temp->next == NULL && temp==unused_block_list)
    {
        allocated_mem = (used_block*)temp;

    	fixed_base_add = temp->base_add + alloc_size;
    	fixed_size = temp->size - alloc_size;

    	new_block = (unused_block*)fixed_base_add;
    	new_block->base_add = fixed_base_add;
    	new_block->size = fixed_size;
    	new_block->next = NULL;
    }
    else
    {
    	return NULL;
    }

    allocated_mem->base_add = (unsigned)(allocated_mem);
    allocated_mem->size = alloc_size;

    return &(allocated_mem->buff); 
}

int free(void* add)
{
    used_block* block = NULL;
    unused_block* new_block=NULL;
    unused_block* temp = NULL;
 
    if(add==NULL || unused_block_list == NULL)
    {
        return 0;
    }

    block = (used_block*)((long unsigned)add-DIFF(used_block,buff));
    new_block = (unused_block*)block;
    new_block->base_add = block->base_add;
    new_block->size = block->size;
    new_block->next=NULL;

    temp = unused_block_list;
    for(;temp!=NULL && temp->next!=NULL; temp=temp->next)
    {
        if(temp->next->base_add > new_block->base_add)
        {
            new_block->next = temp->next;
            temp->next = new_block;
            return 1;
        }
    }

    if(temp->next==NULL && temp==unused_block_list)
    {
        if(temp->base_add > new_block->base_add)
        {
            new_block->next = temp;
            unused_block_list = new_block;
        }
        else
        {
        	temp->next = new_block;
        }
        return  1;
    }

	return 0;
}
