NO_STDLIB=-nostdlib -fno-builtin
NO_PIE=-fno-pie
CFLAG=-Wall -I ../include/ $(NO_STDLIB) $(NO_PIE) -m32 -c
OBJECTS=main.o

main.o:main.c
	$(CC) $(CFLAG) -o main.o main.c

test:$(OBJECTS)
	@mv $(OBJECTS) ../