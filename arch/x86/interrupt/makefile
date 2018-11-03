NO_PIE=-fno-pie
GCC=gcc 
CFLAG=-I ../../../include $(NO_PIE) -m32 -c -o 
NASM=nasm -f elf -o
OBJECTS=hd_interrupt.o hd_interrupt_lib.o

hd_interrupt.o:x86_interrupt.c x86_interrupt.h
	$(GCC) $(CFLAG)  hd_interrupt.o x86_interrupt.c

hd_interrupt_lib.o:x86_interrupt.asm
	$(NASM) hd_interrupt_lib.o x86_interrupt.asm

interrupt:$(OBJECTS)
	mv $(OBJECTS) ../