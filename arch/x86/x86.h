#ifndef X86_H
#define X86_H

#define NULL  0
#define FALSE 0
#define TRUE  1

//  definitions about the intel x86 things
#define KERNEL_ADD        0x500
#define KERNEL_SIZE_ADD   0x502 
#define DRIVER_NUM        0x504
#define DRIVER_DESC_ADD   0x600
#define CODE_SELECTOR     0x10
#define INTERRUPT_DESCRIP 0x8e
#define SYS_CALL_DESCRIP  0X60
#define GDT_ADD           0x100000
#define IDT_ADD           0x110000
#define GDT_LENGTH        0xffff
#define IDT_LENGTH        0x7ff
#define ELE_NUM_IN_GDT_TBL 0x8000
#define ELE_NUM_IN_IDT_TBL 0x100
#define CODE_DATA_DESCRIP 0x10
#define SEGMENT_PRESENT   0x80  
#define CODE_DESCRIP      0xa
#define DATA_DESCRIP      0x2
#define BIG_DESCRIP       0x8000
#define DEFAULT_DESCRIP   0x4000
#define X86_MAX_SIZE      0xffffffff
#define KERNEL_SELECTOR   24
#define KERNEL_EFLAG      0x1202

#define USEFUL_HIGH_ADD   0x200000  // kernel will be load at this address 
#define PAGE_SIZE_PERPTE  0x1000    // an pte element can cover 4K byts
#define PAGE_SIZE_PERPDE  0x400000  // an pde element can cover 4M byts
#define PAGE_TABLE_ADD    0x300000  // PAGE TABLE start from this address

#define LDT_DESCRIB   0x82
#define TSS_DESCRIB   0x89
#define LDT_SELECTOR  0x4
#define SERVICE_AR    1
#define TSS_SIZE      103
#define LDT_SIZE      4
#define VIDEO_GDT     3
#define VIDEO_LDT     2
#define DS_LDT        0
#define DS_GDT        1
#define CS_GDT        2
#define CS_LDT        1

// GDT LDT IDT struct define it's from Intel x86 
typedef struct
{
	unsigned short limit_low,base_low;
	unsigned char  base_mid, ar,      limit_high,base_high;
}gdt;

typedef gdt ldt;

typedef struct
{
	unsigned short offset_low,selector;
	unsigned char  nothing   ,ar;
	unsigned short offset_high;
}idt;

// following hunction defined in "x86_lib.asm"

/* halt cpu for a while*/
void hlt();

/* enable the IRQ */
void sti();
#define x86_enable_IRQ()   sti()

/* disable the IRQ */
void cli();
#define x86_disable_IRQ() cli()

/* load gdt table to lgdt register*/
void lgdt(int limit,int base);

/* loda idt table to lidt register*/
void lidt(int limit,int base);

/* read 8bit from I/O */
unsigned char in_8bits(int port);

/* read 16bit from I/O */
unsigned short in_16bits(int port);

/* read 32bit from I/O */
unsigned in_32bits(int port);

/* write 8bit to I/O */
void out_8bits(unsigned port,unsigned char msg);

/* write 16bit to I/O */
void out_16bits(unsigned port,unsigned short msg);

/* write 32bit to I/O */
void out_32bits(unsigned port,unsigned msg);

/**/
void ltr(int selector);

/* cause interrupt 40, this is for IPC */
void int40(void *address);

/* reset the kernel stack */
void reset_kernel_stack(unsigned new_stack_add);

/* read 32bit data from address*/
unsigned get_memory(void* address);

/*most stupid way to check the memory size*/
unsigned check_memory();

void store_page(void* address);

// reset the kernel selector change the GDT selector to the LDT selector
// it's almost switch the task
void reset_selector(unsigned ldt,unsigned cs,unsigned ds);

// the most function to  switch task 
void far_jump(unsigned base,unsigned selector);

void play();     // for debugging

void playb();    // for debugging

void playc();    // for debugging

void playd();    // for debugging




// following function defined in x86.c
/* set an element in gdt atable */
void set_gdt(gdt* g,unsigned memory_add ,unsigned limit,int ar);

/* set an element in idt table */
void set_idt(idt* i,unsigned handler_add,int selector  ,int ar);

/* initial gdt and idt table and load address in gdt idt register */
void init_gdt_idt();

/* initial x86 platform */
void x86_init_hardware();

// save the driver list into memory
void init_driver_list();


#endif
