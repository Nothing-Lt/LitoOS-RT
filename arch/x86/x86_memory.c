#include "x86.h"
#include "x86_memory.h"

extern unsigned free_memory_add;
extern unsigned memory_size;


// initial page table and store into cr3 register
void x86_set_page(unsigned memory_size)
{
    int i;
    unsigned  temp;
    unsigned* pte_add;
    unsigned* pde_add;
    unsigned  kernel_page_add   = PAGE_TABLE_ADD;
    unsigned  rl_ele_num_in_pte = memory_size / SIZE_OF_PAGE;
    unsigned  rl_ele_num_in_pde = rl_ele_num_in_pte / ELE_NUM_IN_PDE;
    
    pde_add   = (unsigned*)(kernel_page_add);
    pte_add   = (unsigned*)(((unsigned)pde_add)+SIZE_OF_PDE);

    temp = (unsigned)pte_add;
    for(i=0 ; i < rl_ele_num_in_pde ; i++)
    {
        pde_add[i] = temp|PAGE_EXIST_AUTH|PAGE_WRITE_AUTH;
        temp += SIZE_OF_PTE;
    }

    temp = 0;
    for(i=0 ; i < rl_ele_num_in_pte ; i++)
    {
        pte_add[i] = temp|PAGE_EXIST_AUTH|PAGE_USER_AUTH;
        temp += SIZE_OF_PAGE;
    }

    free_memory_add = (free_memory_add + SIZE_OF_PDE) + (ELE_NUM_IN_PDE * SIZE_OF_PTE);
    store_page((unsigned*)kernel_page_add);
}
