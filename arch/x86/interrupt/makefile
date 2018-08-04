GCC=gcc -I ../../../include -m32 -c -o 
NASM=nasm -f elf -o

interrupt:
	$(GCC)  ../../../x86_interrupt.o x86_interrupt.c
	$(NASM) ../../../x86_interrupt_s.o x86_interrupt.asm