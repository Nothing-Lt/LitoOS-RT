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
    unsigned  kernel_page_add=PAGE_TABLE_ADD;
    unsigned  rl_ele_num_in_pte=memory_size/(SIZE_OF_PAGE);
    unsigned  rl_ele_num_in_pde=rl_ele_num_in_pte/ELE_NUM_IN_PDE;
    pde_add   =(unsigned*)(kernel_page_add);
    pte_add   =(unsigned*)(((unsigned)pde_add)+SIZE_OF_PDE);

    temp=(unsigned)pte_add;
    for(i=0;i<rl_ele_num_in_pde;i++)
    {
        pde_add[i]=temp|PAGE_EXIST_AUTH|PAGE_WRITE_AUTH;
        temp+=SIZE_OF_PTE;
    }

    temp=0;
    for(i=0;i<rl_ele_num_in_pte;i++)
    {
        pte_add[i]=temp|PAGE_EXIST_AUTH|PAGE_USER_AUTH;
        temp+=SIZE_OF_PAGE;
    }

    free_memory_add=free_memory_add+SIZE_OF_PDE+(ELE_NUM_IN_PDE*SIZE_OF_PTE);
    store_page((unsigned*)kernel_page_add);
}


// remap the page to another physical address
//
int x86_remap_page(unsigned* page_table,unsigned linear_add,unsigned physicle_add)
{
    unsigned pde_index = (linear_add >> 22) & 0x3ff;
    unsigned pte_index = (linear_add >> 12) & 0x3ff;
    unsigned* pde_add = page_table;
    unsigned* pte_add = NULL; 
    unsigned original_physicle_add = NULL; 
    
    pte_add = (unsigned*)(pde_add[pde_index] & 0xfffff000 );
    original_physicle_add = pte_add[pte_index] & 0xfffff000; 
    
    pte_add[pte_index] = physicle_add | PAGE_EXIST_AUTH | PAGE_WRITE_AUTH;

    return original_physicle_add;
}


/*

unsigned virtul2line(unsigned pid,unsigned virtul_add)
{
  struct task *t=t_list->task_struct_add[pid];
  unsigned base_high=(unsigned)t->this_ldt[1].base_high&0xffff;
  unsigned base_mid =(unsigned)t->this_ldt[1].base_mid&0xff;
  unsigned base_low =(unsigned)t->this_ldt[1].base_low&0xff;
  unsigned base     =base_high<<24|base_mid<<16|base_low;
  return base+virtul_add;
}

unsigned line2physicle(unsigned pid,unsigned line_add)
{
  struct task *t=t_list->task_struct_add[pid];
  unsigned *pde_add=(unsigned*)t->tasc.cr3;
  unsigned pde_index=(line_add&0xffa00000)>>22;
  unsigned pte_index=(line_add&0x3ff000)>>12;
  unsigned add=line_add&0xfff;
  unsigned *pte_add=(unsigned*)(pde_add[pde_index]&0xfffff000);
  unsigned base=pte_add[pte_index]&0xfffff000;
  return base+add; 
}


unsigned alloc_page(int pid,unsigned physicle_add)
{
  struct task *pro=t_list->task_struct_add[pid];
  unsigned *pde_add=(unsigned*)pro->tasc.cr3;
  unsigned *pte_add=(unsigned*)(pde_add[2]&0xfffff000);
  int i=0;
  for(;i<1024;i++)
    {
      if(!pte_add[i])
	{
	  pte_add[i]=physicle_add|PAGE_WRITE|PAGE_USER|PAGE_PRESENT;
	  return (2<<22)+(i<<12);
	}
    }
  return NULL;
}

void free_page(int pid,unsigned line_add)
{
  struct task *pro=t_list->task_struct_add[pid];
  unsigned index_of_pde=(line_add>>22)&0x3ff;
  unsigned index_of_pte=(line_add>>12)&0x3ff;
  unsigned *pde_add=(unsigned*)pro->tasc.cr3;
  unsigned *pte_add=(unsigned*)(pde_add[index_of_pde]&0xfffff000);
  pte_add[index_of_pte]=NULL;
}

void set_page_use(unsigned *pde_add,unsigned line_add)
{
  unsigned index_of_pde=(line_add&0xffc00000)>>22;
  unsigned index_of_pte=(line_add&0x3ff000)>>12;
  unsigned *pte_add=(unsigned*)(pde_add[index_of_pde]&0xfffff000);
  pte_add[index_of_pte]=pte_add[index_of_pte]|PAGE_WRITE|PAGE_USER|PAGE_PRESENT;
  pde_add[index_of_pde]=pde_add[index_of_pde]|PAGE_WRITE|PAGE_USER|PAGE_PRESENT;
}*/