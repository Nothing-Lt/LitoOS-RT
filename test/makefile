NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
GCC=gcc 
CFLAG=-Wall -I ../include/ $(NO_STDLIB) $(NO_PIE) -m32 -c -o
NASM=nasm -f elf -o

test:
	$(GCC) $(CFLAG) ../main.o main.c