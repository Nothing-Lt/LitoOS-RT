NASM=nasm -f bin -o
OBJECTS=boot.bin scnd.bin

boot.bin:boot.asm
	$(NASM) boot.bin boot.asm

scnd.bin:second.asm
	$(NASM) scnd.bin second.asm

boot:$(OBJECTS)
	mv $(OBJECTS) ../
	