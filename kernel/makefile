NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
CFLAG=-I ../include/ $(NO_STDLIB) $(NO_PIE) -Wall -m32 -c
OBJECTS=LitoOS.o task.o memory.o message.o schedule.o interrupt.o

LitoOS.o:LitoOS.c
	$(CC) $(CFLAG) -o LitoOS.o LitoOS.c

task.o:task.c
	$(CC) $(CFLAG) -o task.o task.c

memory.o:memory.c
	$(CC) $(CFLAG) -o memory.o memory.c

message.o:message.c
	$(CC) $(CFLAG) -o message.o message.c

schedule.o:schedule.c
	$(CC) $(CFLAG) -o schedule.o schedule.c

interrupt.o:interrupt.o
	$(CC) $(CFLAG) -o interrupt.o interrupt.c

kernel:$(OBJECTS)
	mv $(OBJECTS) ../
