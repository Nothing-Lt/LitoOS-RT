NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
GCC=gcc 
CFLAG=-Wall -I ../include/ $(NO_STDLIB) $(NO_PIE) -m32 -c -o
NASM=nasm -f elf -o
OBJECTS=LitoOS.o task.o memory.o message.o schedule.o interrupt.o


LitoOS.o:LitoOS.c
	$(GCC) $(CFLAG) LitoOS.o LitoOS.c

task.o:task.c
	$(GCC) $(CFLAG) task.o task.c

memory.o:memory.c
	$(GCC) $(CFLAG) memory.o memory.c

message.o:message.c
	$(GCC) $(CFLAG) message.o message.c

schedule.o:schedule.c
	$(GCC) $(CFLAG) schedule.o schedule.c

interrupt.o:interrupt.o
	$(GCC) $(CFLAG) interrupt.o interrupt.c

kernel:$(OBJECTS)
	mv $(OBJECTS) ../
