
os:
	cd arch && make arch_x86
	cd test && make test
	cd kernel && make kernel
	ld -m elf_i386 main.o memory.o message.o schedual.o task.o interrupt.o x86.o x86_memory.o x86_lib_s.o x86_interrupt.o x86_interrupt_s.o x86_task.o -o sys.bin -Ttext 0x200000 -e main --oformat binary
	# check the fd file if exsists
	if [ ! -x "fd" ]; then mkdir fd; fi
	#############################
	dd if=/dev/zero of=LitoOS.img bs=1k count=1440
	mkfs -t msdos LitoOS.img
	sudo mount -o loop LitoOS.img fd
	# copy sys and the driver into the img file
	sudo cp scnd.bin fd -v
	sudo cp sys.bin fd -v
	sudo cp fs.dv fd -v
	sudo cp hd.dv fd -v
	sudo cp key.dv fd -v
	sudo cp shl.dv fd -v
	sudo cp tty.dv fd -v
	############################################
	sudo umount fd
	# put the boot into the head of img file
	dd if=boot.bin of=LitoOS.img bs=512 count=1 conv=notrunc
	rm *.o

debug:
	bochs -q 'boot:a' 'floppya: 1_44=LitoOS.img, status=inserted'

clean:
	rm *.bin *.img