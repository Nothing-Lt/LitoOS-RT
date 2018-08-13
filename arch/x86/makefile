NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
GCC=gcc -I ../../include $(NO_STDLIB) $(NO_PIE) -c -m32 -o
NASM=nasm -f elf -o

x86:
	 cd boot && make boot 
	 cd interrupt && make interrupt
	 $(GCC)  ../../x86.o x86.c
	 $(GCC)  ../../x86_task.o x86_task.c
	 $(NASM) ../../x86_lib_s.o x86_lib.asm
	 $(GCC)  ../../x86_memory.o x86_memory.c