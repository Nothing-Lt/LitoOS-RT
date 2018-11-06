NO_PIE=-fno-pie
CFLAG=-Wall -I ../../../include $(NO_PIE) -m32 -c
ASFLAG=-f elf
OBJECTS=hd_interrupt.o hd_interrupt_lib.o

hd_interrupt.o:x86_interrupt.c x86_interrupt.h
	$(CC) $(CFLAG) -o hd_interrupt.o x86_interrupt.c

hd_interrupt_lib.o:x86_interrupt.asm
	$(AS) $(ASFLAG) -o hd_interrupt_lib.o x86_interrupt.asm

interrupt:$(OBJECTS)
	@mv $(OBJECTS) ../