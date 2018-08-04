NO_STDLIB=-nostdlib -fno-builtin
GCC=gcc -I ../include/ $(NO_STDLIB) -m32 -c -o
NASM=nasm -f elf -o

kernel:
	$(GCC) ../memory.o memory.c