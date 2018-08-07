NO_STDLIB=-nostdlib -fno-builtin
GCC=gcc -I ../include/ $(NO_STDLIB) -m32 -c -o
NASM=nasm -f elf -o

kernel:
	$(GCC) ../task.o task.c
	$(GCC) ../memory.o memory.c
	$(GCC) ../message.o message.c
	$(GCC) ../schedual.o schedual.c
	$(GCC) ../interrupt.o interrupt.c