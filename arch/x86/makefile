NO_STDLIB=-nostdlib -fno-builtin
GCC=gcc -c -m32 -o
NASM=nasm -f elf -o
x86:
	 cd boot && make boot 
	 cd interrupt && make interrupt
	 $(GCC)  ../../x86.o x86.c
	 $(NASM) ../../x86_lib_s.o x86_lib.asm
	 $(GCC)  ../../x86_memory.o x86_memory.c