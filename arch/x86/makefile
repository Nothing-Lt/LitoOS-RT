NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
CFLAG=-Wall -I ../../include $(NO_STDLIB) $(NO_PIE) -m32 -c
ASFLAG=-f elf 
OBJECTS=boot.bin scnd.bin hd_interrupt.o hd_interrupt_lib.o hd.o hd_lib.o hd_task.o hd_memory.o 

boot.bin:
	@cd boot && make boot CC=$(CC) AS=$(AS)

scnd.bin:
	@cd boot && make boot CC=$(CC) AS=$(AS)

hd_interrupt.o:
	@cd interrupt && make interrupt CC=$(CC) AS=$(AS)

hd_interrupt_lib.o:
	@cd interrupt && make interrupt CC=$(CC) AS=$(AS)

hd.o:x86.c x86.h
	$(CC) $(CFLAG) -o hd.o x86.c

hd_lib.o:x86_lib.asm
	$(AS) $(ASFLAG) -o hd_lib.o x86_lib.asm

hd_task.o:x86_task.c x86_task.h
	$(CC) $(CFLAG) -o hd_task.o x86_task.c

hd_memory.o:x86_memory.c x86_memory.h
	$(CC) $(CFLAG) -o hd_memory.o x86_memory.c

x86:$(OBJECTS)
	@mv $(OBJECTS) ../