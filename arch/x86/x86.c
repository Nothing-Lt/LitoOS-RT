#include "x86.h"

#include "x86_memory.h"
#include "interrupt/x86_interrupt.h"

extern unsigned kernel_size;
extern unsigned free_memory_add;
extern unsigned memory_size;

gdt* gdt_addr;
idt* idt_addr;

void x86_init_hardware()
{
    kernel_size =get_memory((void*)KERNEL_SIZE_ADD)<<4;
    init_gdt_idt(kernel_size);

    memory_size =check_memory();

    x86_set_page(memory_size);
}

void init_gdt_idt(unsigned kernel_size)
{
    int i;
    gdt_addr=(gdt*)GDT_ADD;
 
    for( i=0 ; i<ELE_NUM_IN_GDT_TBL ; i++)
    {
        set_gdt(&gdt_addr[i],0,0,0);
    }
 
    set_gdt(&gdt_addr[1],0,X86_MAX_SIZE,DEFAULT_DESCRIP|SEGMENT_PRESENT|CODE_DATA_DESCRIP|DATA_DESCRIP);
    set_gdt(&gdt_addr[2],0,X86_MAX_SIZE,DEFAULT_DESCRIP|SEGMENT_PRESENT|CODE_DATA_DESCRIP|CODE_DESCRIP);
    lgdt(GDT_LENGTH,GDT_ADD);
	
    free_memory_add=(GDT_ADD+ELE_NUM_IN_GDT_TBL*sizeof(gdt));
	
    if((GDT_ADD+ELE_NUM_IN_GDT_TBL*sizeof(gdt))&0xf!=0)
    {
        free_memory_add=(((GDT_ADD+ELE_NUM_IN_GDT_TBL*sizeof(gdt))&0xfffffff0)+8);
    }
	
    idt_addr=(idt*)free_memory_add;

    set_idt(&idt_addr[0x00],(unsigned)asm_handle0x00,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x01],(unsigned)asm_handle0x01,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x02],(unsigned)asm_handle0x02,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x03],(unsigned)asm_handle0x03,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x04],(unsigned)asm_handle0x04,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x05],(unsigned)asm_handle0x05,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x06],(unsigned)asm_handle0x06,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x07],(unsigned)asm_handle0x07,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x08],(unsigned)asm_handle0x08,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x09],(unsigned)asm_handle0x09,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x0a],(unsigned)asm_handle0x0a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x0b],(unsigned)asm_handle0x0b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x0c],(unsigned)asm_handle0x0c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x0d],(unsigned)asm_handle0x0d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x0e],(unsigned)asm_handle0x0e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x0f],(unsigned)asm_handle0x0f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x10],(unsigned)asm_handle0x10,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x11],(unsigned)asm_handle0x11,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x12],(unsigned)asm_handle0x12,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x13],(unsigned)asm_handle0x13,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x14],(unsigned)asm_handle0x14,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x15],(unsigned)asm_handle0x15,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x16],(unsigned)asm_handle0x16,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x17],(unsigned)asm_handle0x17,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x18],(unsigned)asm_handle0x18,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x19],(unsigned)asm_handle0x19,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x1a],(unsigned)asm_handle0x1a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x1b],(unsigned)asm_handle0x1b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x1c],(unsigned)asm_handle0x1c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x1d],(unsigned)asm_handle0x1d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x1e],(unsigned)asm_handle0x1e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x1f],(unsigned)asm_handle0x1f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x20],(unsigned)asm_handle0x20,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x21],(unsigned)asm_handle0x21,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x22],(unsigned)asm_handle0x22,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x23],(unsigned)asm_handle0x23,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x24],(unsigned)asm_handle0x24,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x25],(unsigned)asm_handle0x25,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x26],(unsigned)asm_handle0x26,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x27],(unsigned)asm_handle0x27,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x28],(unsigned)asm_handle0x28,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x29],(unsigned)asm_handle0x29,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x2a],(unsigned)asm_handle0x2a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x2b],(unsigned)asm_handle0x2b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x2c],(unsigned)asm_handle0x2c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x2d],(unsigned)asm_handle0x2d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x2e],(unsigned)asm_handle0x2e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x2f],(unsigned)asm_handle0x2f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x30],(unsigned)asm_handle0x30,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x31],(unsigned)asm_handle0x31,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x32],(unsigned)asm_handle0x32,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x33],(unsigned)asm_handle0x33,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x34],(unsigned)asm_handle0x34,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x35],(unsigned)asm_handle0x35,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x36],(unsigned)asm_handle0x36,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x37],(unsigned)asm_handle0x37,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x38],(unsigned)asm_handle0x38,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x39],(unsigned)asm_handle0x39,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x3a],(unsigned)asm_handle0x3a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x3b],(unsigned)asm_handle0x3b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x3c],(unsigned)asm_handle0x3c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x3d],(unsigned)asm_handle0x3d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x3e],(unsigned)asm_handle0x3e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x3f],(unsigned)asm_handle0x3f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x40],(unsigned)asm_send_recv ,CODE_SELECTOR,INTERRUPT_DESCRIP|SYS_CALL_DESCRIP);
    set_idt(&idt_addr[0x41],(unsigned)asm_handle0x41,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x42],(unsigned)asm_handle0x42,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x43],(unsigned)asm_handle0x43,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x44],(unsigned)asm_handle0x44,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x45],(unsigned)asm_handle0x45,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x46],(unsigned)asm_handle0x46,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x47],(unsigned)asm_handle0x47,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x48],(unsigned)asm_handle0x48,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x49],(unsigned)asm_handle0x49,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x4a],(unsigned)asm_handle0x4a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x4b],(unsigned)asm_handle0x4b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x4c],(unsigned)asm_handle0x4c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x4d],(unsigned)asm_handle0x4d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x4e],(unsigned)asm_handle0x4e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x4f],(unsigned)asm_handle0x4f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x50],(unsigned)asm_handle0x50,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x51],(unsigned)asm_handle0x51,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x52],(unsigned)asm_handle0x52,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x53],(unsigned)asm_handle0x53,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x54],(unsigned)asm_handle0x54,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x55],(unsigned)asm_handle0x55,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x56],(unsigned)asm_handle0x56,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x57],(unsigned)asm_handle0x57,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x58],(unsigned)asm_handle0x58,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x59],(unsigned)asm_handle0x59,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x5a],(unsigned)asm_handle0x5a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x5b],(unsigned)asm_handle0x5b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x5c],(unsigned)asm_handle0x5c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x5d],(unsigned)asm_handle0x5d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x5e],(unsigned)asm_handle0x5e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x5f],(unsigned)asm_handle0x5f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x60],(unsigned)asm_handle0x60,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x61],(unsigned)asm_handle0x61,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x62],(unsigned)asm_handle0x62,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x63],(unsigned)asm_handle0x63,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x64],(unsigned)asm_handle0x64,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x65],(unsigned)asm_handle0x65,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x66],(unsigned)asm_handle0x66,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x67],(unsigned)asm_handle0x67,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x68],(unsigned)asm_handle0x68,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x69],(unsigned)asm_handle0x69,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x6a],(unsigned)asm_handle0x6a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x6b],(unsigned)asm_handle0x6b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x6c],(unsigned)asm_handle0x6c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x6d],(unsigned)asm_handle0x6d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x6e],(unsigned)asm_handle0x6e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x6f],(unsigned)asm_handle0x6f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x70],(unsigned)asm_handle0x70,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x71],(unsigned)asm_handle0x71,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x72],(unsigned)asm_handle0x72,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x73],(unsigned)asm_handle0x73,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x74],(unsigned)asm_handle0x74,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x75],(unsigned)asm_handle0x75,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x76],(unsigned)asm_handle0x76,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x77],(unsigned)asm_handle0x77,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x78],(unsigned)asm_handle0x78,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x79],(unsigned)asm_handle0x79,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x7a],(unsigned)asm_handle0x7a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x7b],(unsigned)asm_handle0x7b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x7c],(unsigned)asm_handle0x7c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x7d],(unsigned)asm_handle0x7d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x7e],(unsigned)asm_handle0x7e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x7f],(unsigned)asm_handle0x7f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x80],(unsigned)asm_handle0x80,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x81],(unsigned)asm_handle0x81,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x82],(unsigned)asm_handle0x82,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x83],(unsigned)asm_handle0x83,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x84],(unsigned)asm_handle0x84,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x85],(unsigned)asm_handle0x85,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x86],(unsigned)asm_handle0x86,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x87],(unsigned)asm_handle0x87,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x88],(unsigned)asm_handle0x88,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x89],(unsigned)asm_handle0x89,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x8a],(unsigned)asm_handle0x8a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x8b],(unsigned)asm_handle0x8b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x8c],(unsigned)asm_handle0x8c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x8d],(unsigned)asm_handle0x8d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x8e],(unsigned)asm_handle0x8e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x8f],(unsigned)asm_handle0x8f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x90],(unsigned)asm_handle0x90,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x91],(unsigned)asm_handle0x91,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x92],(unsigned)asm_handle0x92,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x93],(unsigned)asm_handle0x93,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x94],(unsigned)asm_handle0x94,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x95],(unsigned)asm_handle0x95,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x96],(unsigned)asm_handle0x96,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x97],(unsigned)asm_handle0x97,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x98],(unsigned)asm_handle0x98,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x99],(unsigned)asm_handle0x99,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x9a],(unsigned)asm_handle0x9a,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x9b],(unsigned)asm_handle0x9b,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x9c],(unsigned)asm_handle0x9c,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x9d],(unsigned)asm_handle0x9d,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x9e],(unsigned)asm_handle0x9e,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0x9f],(unsigned)asm_handle0x9f,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa0],(unsigned)asm_handle0xa0,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa1],(unsigned)asm_handle0xa1,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa2],(unsigned)asm_handle0xa2,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa3],(unsigned)asm_handle0xa3,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa4],(unsigned)asm_handle0xa4,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa5],(unsigned)asm_handle0xa5,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa6],(unsigned)asm_handle0xa6,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa7],(unsigned)asm_handle0xa7,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa8],(unsigned)asm_handle0xa8,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xa9],(unsigned)asm_handle0xa9,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xaa],(unsigned)asm_handle0xaa,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xab],(unsigned)asm_handle0xab,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xac],(unsigned)asm_handle0xac,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xad],(unsigned)asm_handle0xad,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xae],(unsigned)asm_handle0xae,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xaf],(unsigned)asm_handle0xaf,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb0],(unsigned)asm_handle0xb0,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb1],(unsigned)asm_handle0xb1,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb2],(unsigned)asm_handle0xb2,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb3],(unsigned)asm_handle0xb3,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb4],(unsigned)asm_handle0xb4,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb5],(unsigned)asm_handle0xb5,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb6],(unsigned)asm_handle0xb6,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb7],(unsigned)asm_handle0xb7,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb8],(unsigned)asm_handle0xb8,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xb9],(unsigned)asm_handle0xb9,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xba],(unsigned)asm_handle0xba,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xbb],(unsigned)asm_handle0xbb,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xbc],(unsigned)asm_handle0xbc,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xbd],(unsigned)asm_handle0xbd,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xbe],(unsigned)asm_handle0xbe,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xbf],(unsigned)asm_handle0xbf,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc0],(unsigned)asm_handle0xc0,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc1],(unsigned)asm_handle0xc1,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc2],(unsigned)asm_handle0xc2,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc3],(unsigned)asm_handle0xc3,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc4],(unsigned)asm_handle0xc4,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc5],(unsigned)asm_handle0xc5,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc6],(unsigned)asm_handle0xc6,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc7],(unsigned)asm_handle0xc7,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc8],(unsigned)asm_handle0xc8,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xc9],(unsigned)asm_handle0xc9,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xca],(unsigned)asm_handle0xca,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xcb],(unsigned)asm_handle0xcb,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xcc],(unsigned)asm_handle0xcc,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xcd],(unsigned)asm_handle0xcd,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xce],(unsigned)asm_handle0xce,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xcf],(unsigned)asm_handle0xcf,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd0],(unsigned)asm_handle0xd0,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd1],(unsigned)asm_handle0xd1,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd2],(unsigned)asm_handle0xd2,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd3],(unsigned)asm_handle0xd3,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd4],(unsigned)asm_handle0xd4,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd5],(unsigned)asm_handle0xd5,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd6],(unsigned)asm_handle0xd6,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd7],(unsigned)asm_handle0xd7,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd8],(unsigned)asm_handle0xd8,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xd9],(unsigned)asm_handle0xd9,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xda],(unsigned)asm_handle0xda,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xdb],(unsigned)asm_handle0xdb,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xdc],(unsigned)asm_handle0xdc,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xdd],(unsigned)asm_handle0xdd,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xde],(unsigned)asm_handle0xde,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xdf],(unsigned)asm_handle0xdf,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe0],(unsigned)asm_handle0xe0,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe1],(unsigned)asm_handle0xe1,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe2],(unsigned)asm_handle0xe2,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe3],(unsigned)asm_handle0xe3,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe4],(unsigned)asm_handle0xe4,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe5],(unsigned)asm_handle0xe5,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe6],(unsigned)asm_handle0xe6,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe7],(unsigned)asm_handle0xe7,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe8],(unsigned)asm_handle0xe8,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xe9],(unsigned)asm_handle0xe9,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xea],(unsigned)asm_handle0xea,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xeb],(unsigned)asm_handle0xeb,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xec],(unsigned)asm_handle0xec,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xed],(unsigned)asm_handle0xed,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xee],(unsigned)asm_handle0xee,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xef],(unsigned)asm_handle0xef,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf0],(unsigned)asm_handle0xf0,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf1],(unsigned)asm_handle0xf1,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf2],(unsigned)asm_handle0xf2,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf3],(unsigned)asm_handle0xf3,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf4],(unsigned)asm_handle0xf4,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf5],(unsigned)asm_handle0xf5,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf6],(unsigned)asm_handle0xf6,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf7],(unsigned)asm_handle0xf7,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf8],(unsigned)asm_handle0xf8,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xf9],(unsigned)asm_handle0xf9,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xfa],(unsigned)asm_handle0xfa,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xfb],(unsigned)asm_handle0xfb,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xfc],(unsigned)asm_handle0xfc,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xfd],(unsigned)asm_handle0xfd,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xfe],(unsigned)asm_handle0xfe,CODE_SELECTOR,INTERRUPT_DESCRIP);
    set_idt(&idt_addr[0xff],(unsigned)asm_handle0xff,CODE_SELECTOR,INTERRUPT_DESCRIP);
    
    lidt(IDT_LENGTH,(unsigned)idt_addr);
    free_memory_add=(((unsigned)free_memory_add)+ELE_NUM_IN_IDT_TBL*sizeof(idt));
}

void set_idt(idt *i,unsigned offset,int selector,int ar)
{
    i->offset_low = offset   & 0xffff;
    i->selector   = selector & 0xffff;
    i->nothing    = 0;
    i->ar         = ar & 0xff;
    i->offset_high= (offset>>16) & 0xffff;
}

void set_gdt(gdt *g,unsigned base,unsigned limit,int ar)
{
    if(limit>0xfffff)
    {
        ar   = ar | BIG_DESCRIP;
        limit= limit / 0x1000;
    }
    g->limit_low = limit     & 0xffff;
    g->base_low  = base      & 0xffff;
    g->base_mid  = (base>>16)& 0xff;
    g->base_high = (base>>24)& 0xff;
    g->ar        = ar        & 0xff;
    g->limit_high= (ar>>8)   & 0xf0 | (limit>>16) & 0xf;
}

unsigned find_empty_gdt()
{
    unsigned i;

    for(i=1;i<ELE_NUM_IN_GDT_TBL;i++)
    {
        if(gdt_addr[i].ar==NULL&&gdt_addr[i+1].ar==NULL)
        {
            return i;
        }
    }
    return 0;
}

