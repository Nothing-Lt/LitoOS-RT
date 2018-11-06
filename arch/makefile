OBJECTS=boot.bin hd_interrupt.o hd_interrupt_lib.o hd.o hd_lib.o hd_task.o hd_memory.o 

arch_x86:
	@cd x86 && make x86 CC=$(CC) AS=$(AS) --no-print-directory
	@mv $(OBJECTS) scnd.bin ../