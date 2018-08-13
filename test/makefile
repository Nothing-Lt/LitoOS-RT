NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
GCC=gcc -I ../include/ $(NO_STDLIB) $(NO_PIE) -m32 -c -o
NASM=nasm -f elf -o

test:
	$(GCC) ../main.o main.c