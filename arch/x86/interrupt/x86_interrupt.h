#ifndef X86_INTERRUPT_H
#define X86_INTERRUPT_H

#define PAGE_PRESENT       1
#define PAGE_READ          0
#define PAGE_WRITE         2
#define PAGE_USER          4
#define PAGE_SUPER         0
#define HANDLE_NUM         0x20
#define HANDLE_NUM_EC      10
#define HANDLE_NUM_HARD    0X10
#define REUSEABLE_IRQLINE  0x41
#define SOFT_IRQLINE_BEGIN 0x00   //[0x00,0x1f] for software interrupt or exception
#define SOFT_IRQLINE_END   0x1f
#define HARD_IRQLINE_BEGIN 0x20
#define HARD_IRQLINE_END   0xff   //[0x20,0xff] for hardware interrupt
#define IRQLINE_NUMBER     0x100

// normal exception handler list 
typedef struct
{
    void* function_pointer[IRQLINE_NUMBER];
}handle_list;

// software interrupt handler the system call interface
typedef struct
{
    void (*send_recv)(void* msg);//(struct message *msg);
}send_recv_s;

// software exception handler
void asm_handle0x00();
void asm_handle0x01();
void asm_handle0x02();
void asm_handle0x03();
void asm_handle0x04();
void asm_handle0x05();
void asm_handle0x06();
void asm_handle0x07();
void asm_handle0x08();
void asm_handle0x09();
void asm_handle0x0a();
void asm_handle0x0b();
void asm_handle0x0c();
void asm_handle0x0d();
void asm_handle0x0e();
void asm_handle0x0f();

void asm_handle0x10();
void asm_handle0x11();
void asm_handle0x12();
void asm_handle0x13();
void asm_handle0x14();
void asm_handle0x15();
void asm_handle0x16();
void asm_handle0x17();
void asm_handle0x18();
void asm_handle0x19();
void asm_handle0x1a();
void asm_handle0x1b();
void asm_handle0x1c();
void asm_handle0x1d();
void asm_handle0x1e();
void asm_handle0x1f();

// hardware interrupt handler
void asm_handle0x20();
void asm_handle0x21();
void asm_handle0x22();
void asm_handle0x23();
void asm_handle0x24();
void asm_handle0x25();
void asm_handle0x26();
void asm_handle0x27();
void asm_handle0x28();
void asm_handle0x29();
void asm_handle0x2a();
void asm_handle0x2b();
void asm_handle0x2c();
void asm_handle0x2d();
void asm_handle0x2e();
void asm_handle0x2f();

void asm_handle0x30();
void asm_handle0x31();
void asm_handle0x32();
void asm_handle0x33();
void asm_handle0x34();
void asm_handle0x35();
void asm_handle0x36();
void asm_handle0x37();
void asm_handle0x38();
void asm_handle0x39();
void asm_handle0x3a();
void asm_handle0x3b();
void asm_handle0x3c();
void asm_handle0x3d();
void asm_handle0x3e();
void asm_handle0x3f();

void asm_handle0x41();
void asm_handle0x42();
void asm_handle0x43();
void asm_handle0x44();
void asm_handle0x45();
void asm_handle0x46();
void asm_handle0x47();
void asm_handle0x48();
void asm_handle0x49();
void asm_handle0x4a();
void asm_handle0x4b();
void asm_handle0x4c();
void asm_handle0x4d();
void asm_handle0x4e();
void asm_handle0x4f();

void asm_handle0x50();
void asm_handle0x51();
void asm_handle0x52();
void asm_handle0x53();
void asm_handle0x54();
void asm_handle0x55();
void asm_handle0x56();
void asm_handle0x57();
void asm_handle0x58();
void asm_handle0x59();
void asm_handle0x5a();
void asm_handle0x5b();
void asm_handle0x5c();
void asm_handle0x5d();
void asm_handle0x5e();
void asm_handle0x5f();

void asm_handle0x60();
void asm_handle0x61();
void asm_handle0x62();
void asm_handle0x63();
void asm_handle0x64();
void asm_handle0x65();
void asm_handle0x66();
void asm_handle0x67();
void asm_handle0x68();
void asm_handle0x69();
void asm_handle0x6a();
void asm_handle0x6b();
void asm_handle0x6c();
void asm_handle0x6d();
void asm_handle0x6e();
void asm_handle0x6f();

void asm_handle0x70();
void asm_handle0x71();
void asm_handle0x72();
void asm_handle0x73();
void asm_handle0x74();
void asm_handle0x75();
void asm_handle0x76();
void asm_handle0x77();
void asm_handle0x78();
void asm_handle0x79();
void asm_handle0x7a();
void asm_handle0x7b();
void asm_handle0x7c();
void asm_handle0x7d();
void asm_handle0x7e();
void asm_handle0x7f();

void asm_handle0x80();
void asm_handle0x81();
void asm_handle0x82();
void asm_handle0x83();
void asm_handle0x84();
void asm_handle0x85();
void asm_handle0x86();
void asm_handle0x87();
void asm_handle0x88();
void asm_handle0x89();
void asm_handle0x8a();
void asm_handle0x8b();
void asm_handle0x8c();
void asm_handle0x8d();
void asm_handle0x8e();
void asm_handle0x8f();

void asm_handle0x90();
void asm_handle0x91();
void asm_handle0x92();
void asm_handle0x93();
void asm_handle0x94();
void asm_handle0x95();
void asm_handle0x96();
void asm_handle0x97();
void asm_handle0x98();
void asm_handle0x99();
void asm_handle0x9a();
void asm_handle0x9b();
void asm_handle0x9c();
void asm_handle0x9d();
void asm_handle0x9e();
void asm_handle0x9f();

void asm_handle0xa0();
void asm_handle0xa1();
void asm_handle0xa2();
void asm_handle0xa3();
void asm_handle0xa4();
void asm_handle0xa5();
void asm_handle0xa6();
void asm_handle0xa7();
void asm_handle0xa8();
void asm_handle0xa9();
void asm_handle0xaa();
void asm_handle0xab();
void asm_handle0xac();
void asm_handle0xad();
void asm_handle0xae();
void asm_handle0xaf();

void asm_handle0xb0();
void asm_handle0xb1();
void asm_handle0xb2();
void asm_handle0xb3();
void asm_handle0xb4();
void asm_handle0xb5();
void asm_handle0xb6();
void asm_handle0xb7();
void asm_handle0xb8();
void asm_handle0xb9();
void asm_handle0xba();
void asm_handle0xbb();
void asm_handle0xbc();
void asm_handle0xbd();
void asm_handle0xbe();
void asm_handle0xbf();

void asm_handle0xc0();
void asm_handle0xc1();
void asm_handle0xc2();
void asm_handle0xc3();
void asm_handle0xc4();
void asm_handle0xc5();
void asm_handle0xc6();
void asm_handle0xc7();
void asm_handle0xc8();
void asm_handle0xc9();
void asm_handle0xca();
void asm_handle0xcb();
void asm_handle0xcc();
void asm_handle0xcd();
void asm_handle0xce();
void asm_handle0xcf();

void asm_handle0xd0();
void asm_handle0xd1();
void asm_handle0xd2();
void asm_handle0xd3();
void asm_handle0xd4();
void asm_handle0xd5();
void asm_handle0xd6();
void asm_handle0xd7();
void asm_handle0xd8();
void asm_handle0xd9();
void asm_handle0xda();
void asm_handle0xdb();
void asm_handle0xdc();
void asm_handle0xdd();
void asm_handle0xde();
void asm_handle0xdf();

void asm_handle0xe0();
void asm_handle0xe1();
void asm_handle0xe2();
void asm_handle0xe3();
void asm_handle0xe4();
void asm_handle0xe5();
void asm_handle0xe6();
void asm_handle0xe7();
void asm_handle0xe8();
void asm_handle0xe9();
void asm_handle0xea();
void asm_handle0xeb();
void asm_handle0xec();
void asm_handle0xed();
void asm_handle0xee();
void asm_handle0xef();

void asm_handle0xf0();
void asm_handle0xf1();
void asm_handle0xf2();
void asm_handle0xf3();
void asm_handle0xf4();
void asm_handle0xf5();
void asm_handle0xf6();
void asm_handle0xf7();
void asm_handle0xf8();
void asm_handle0xf9();
void asm_handle0xfa();
void asm_handle0xfb();
void asm_handle0xfc();
void asm_handle0xfd();
void asm_handle0xfe();
void asm_handle0xff();

//extern void asm_handle0x2e();
void handle0x00(unsigned error_ip,unsigned error_code);
void handle0x01(unsigned error_ip,unsigned error_code);
void handle0x02(unsigned error_ip,unsigned error_code);
void handle0x03(unsigned error_ip,unsigned error_code);
void handle0x04(unsigned error_ip,unsigned error_code);
void handle0x05(unsigned error_ip,unsigned error_code);
void handle0x06(unsigned error_ip,unsigned error_code);
void handle0x07(unsigned error_ip,unsigned error_code);
void handle0x08(unsigned error_ip,unsigned error_code);
void handle0x09(unsigned error_ip,unsigned error_code);
void handle0x0a(unsigned error_ip,unsigned error_code);
void handle0x0b(unsigned error_ip,unsigned error_code);
void handle0x0c(unsigned error_ip,unsigned error_code);
void handle0x0d(unsigned error_ip,unsigned error_code);
void handle0x0e(unsigned error_ip,unsigned error_code);
void handle0x0f(unsigned error_ip,unsigned error_code);
void handle0x10(unsigned error_ip,unsigned error_code);
void handle0x11(unsigned error_ip,unsigned error_code);
void handle0x12(unsigned error_ip,unsigned error_code);
void handle0x13(unsigned error_ip,unsigned error_code);
void handle0x14(unsigned error_ip,unsigned error_code);
void handle0x15(unsigned error_ip,unsigned error_code);
void handle0x16(unsigned error_ip,unsigned error_code);
void handle0x17(unsigned error_ip,unsigned error_code);
void handle0x18(unsigned error_ip,unsigned error_code);
void handle0x19(unsigned error_ip,unsigned error_code);
void handle0x1a(unsigned error_ip,unsigned error_code);
void handle0x1b(unsigned error_ip,unsigned error_code);
void handle0x1c(unsigned error_ip,unsigned error_code);
void handle0x1d(unsigned error_ip,unsigned error_code);
void handle0x1e(unsigned error_ip,unsigned error_code);
void handle0x1f(unsigned error_ip,unsigned error_code);

// hardware handler
void handle0x20();
void handle0x21();
void handle0x22();
void handle0x23();
void handle0x24();
void handle0x25();
void handle0x26();
void handle0x27();
void handle0x28();
void handle0x29();
void handle0x2a();
void handle0x2b();
void handle0x2c();
void handle0x2d();
void handle0x2e();
void handle0x2f();

void handle0x30();
void handle0x31();
void handle0x32();
void handle0x33();
void handle0x34();
void handle0x35();
void handle0x36();
void handle0x37();
void handle0x38();
void handle0x39();
void handle0x3a();
void handle0x3b();
void handle0x3c();
void handle0x3d();
void handle0x3e();
void handle0x3f();

void handle0x40();
void handle0x41();
void handle0x42();
void handle0x43();
void handle0x44();
void handle0x45();
void handle0x46();
void handle0x47();
void handle0x48();
void handle0x49();
void handle0x4a();
void handle0x4b();
void handle0x4c();
void handle0x4d();
void handle0x4e();
void handle0x4f();

void handle0x50();
void handle0x51();
void handle0x52();
void handle0x53();
void handle0x54();
void handle0x55();
void handle0x56();
void handle0x57();
void handle0x58();
void handle0x59();
void handle0x5a();
void handle0x5b();
void handle0x5c();
void handle0x5d();
void handle0x5e();
void handle0x5f();

void handle0x60();
void handle0x61();
void handle0x62();
void handle0x63();
void handle0x64();
void handle0x65();
void handle0x66();
void handle0x67();
void handle0x68();
void handle0x69();
void handle0x6a();
void handle0x6b();
void handle0x6c();
void handle0x6d();
void handle0x6e();
void handle0x6f();

void handle0x70();
void handle0x71();
void handle0x72();
void handle0x73();
void handle0x74();
void handle0x75();
void handle0x76();
void handle0x77();
void handle0x78();
void handle0x79();
void handle0x7a();
void handle0x7b();
void handle0x7c();
void handle0x7d();
void handle0x7e();
void handle0x7f();

void handle0x80();
void handle0x81();
void handle0x82();
void handle0x83();
void handle0x84();
void handle0x85();
void handle0x86();
void handle0x87();
void handle0x88();
void handle0x89();
void handle0x8a();
void handle0x8b();
void handle0x8c();
void handle0x8d();
void handle0x8e();
void handle0x8f();

void handle0x90();
void handle0x91();
void handle0x92();
void handle0x93();
void handle0x94();
void handle0x95();
void handle0x96();
void handle0x97();
void handle0x98();
void handle0x99();
void handle0x9a();
void handle0x9b();
void handle0x9c();
void handle0x9d();
void handle0x9e();
void handle0x9f();

void handle0xa0();
void handle0xa1();
void handle0xa2();
void handle0xa3();
void handle0xa4();
void handle0xa5();
void handle0xa6();
void handle0xa7();
void handle0xa8();
void handle0xa9();
void handle0xaa();
void handle0xab();
void handle0xac();
void handle0xad();
void handle0xae();
void handle0xaf();

void handle0xb0();
void handle0xb1();
void handle0xb2();
void handle0xb3();
void handle0xb4();
void handle0xb5();
void handle0xb6();
void handle0xb7();
void handle0xb8();
void handle0xb9();
void handle0xba();
void handle0xbb();
void handle0xbc();
void handle0xbd();
void handle0xbe();
void handle0xbf();

void handle0xc0();
void handle0xc1();
void handle0xc2();
void handle0xc3();
void handle0xc4();
void handle0xc5();
void handle0xc6();
void handle0xc7();
void handle0xc8();
void handle0xc9();
void handle0xca();
void handle0xcb();
void handle0xcc();
void handle0xcd();
void handle0xce();
void handle0xcf();

void handle0xd0();
void handle0xd1();
void handle0xd2();
void handle0xd3();
void handle0xd4();
void handle0xd5();
void handle0xd6();
void handle0xd7();
void handle0xd8();
void handle0xd9();
void handle0xda();
void handle0xdb();
void handle0xdc();
void handle0xdd();
void handle0xde();
void handle0xdf();

void handle0xe0();
void handle0xe1();
void handle0xe2();
void handle0xe3();
void handle0xe4();
void handle0xe5();
void handle0xe6();
void handle0xe7();
void handle0xe8();
void handle0xe9();
void handle0xea();
void handle0xeb();
void handle0xec();
void handle0xed();
void handle0xee();
void handle0xef();

void handle0xf0();
void handle0xf1();
void handle0xf2();
void handle0xf3();
void handle0xf4();
void handle0xf5();
void handle0xf6();
void handle0xf7();
void handle0xf8();
void handle0xf9();
void handle0xfa();
void handle0xfb();
void handle0xfc();
void handle0xfd();
void handle0xfe();
void handle0xff();

//default handler for software and hardware interrupt
void default_handler_soft(unsigned error_ip,unsigned error_code);
void default_handler_hard(unsigned irq_num);

// this function for setting handler of an IRQ line,
// and this function is only callde by system kernel,
// no user application could call this function.
int set_IRQLINE_handler(unsigned irq,void* function);

int remove_IRQLINE_handler(unsigned irq);

// default hardware interrupt handler
void default_send_recv(void* msg);

// the asm code call this function
void sys_send_recv(void *msg);

// this handler write into the IDT in intel
void asm_send_recv();

// set handler to the specified interrupt number
void set_handler(unsigned num,void *function);


#endif