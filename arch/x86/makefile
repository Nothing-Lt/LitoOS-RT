NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
GCC=gcc
CFLAG=-Wall -I ../../include $(NO_STDLIB) $(NO_PIE) -c -m32 -o
NASM=nasm -f elf -o
OBJECTS=boot.bin scnd.bin hd_interrupt.o hd_interrupt_lib.o hd.o hd_lib.o hd_task.o hd_memory.o 

boot.bin:
	cd boot && make boot

scnd.bin:
	cd boot && make boot

hd_interrupt.o:
	cd interrupt && make interrupt

hd_interrupt_lib.o:
	cd interrupt && make interrupt

hd.o:x86.c x86.h
	$(GCC) $(CFLAG) hd.o x86.c

hd_lib.o:x86_lib.asm
	$(NASM) hd_lib.o x86_lib.asm

hd_task.o:x86_task.c x86_task.h
	$(GCC)  $(CFLAG) hd_task.o x86_task.c

hd_memory.o:x86_memory.c x86_memory.h
	$(GCC)  $(CFLAG) hd_memory.o x86_memory.c

x86:$(OBJECTS)
	mv $(OBJECTS) ../