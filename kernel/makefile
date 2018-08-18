NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
GCC=gcc -I ../include/ $(NO_STDLIB) $(NO_PIE) -m32 -c -o
NASM=nasm -f elf -o

kernel:
	$(GCC) ../task.o task.c
	$(GCC) ../memory.o memory.c
	$(GCC) ../message.o message.c
	$(GCC) ../schedule.o schedule.c
	$(GCC) ../interrupt.o interrupt.c