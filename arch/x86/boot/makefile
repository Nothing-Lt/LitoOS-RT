ASFLAG=-f bin -o
OBJECTS=boot.bin scnd.bin

boot.bin:boot.asm
	$(AS) $(ASFLAG) boot.bin boot.asm

scnd.bin:second.asm
	$(AS) $(ASFLAG) scnd.bin second.asm

boot:$(OBJECTS)
	@mv $(OBJECTS) ../
	