CC = i686-elf-gcc

main:
	$(CC) -std=gnu99 -ffreestanding -g -c start.s -o start.o
	$(CC) -std=gnu99 -ffreestanding -g -c kernel.c -o kernel.o
	$(CC) -ffreestanding -nostdlib -g -T linker.ld start.o kernel.o -o dragkern.elf -lgcc
	mkdir -p isoroot/boot/grub/
	cp grub.cfg isoroot/boot/grub/grub.cfg
	cp dragkern.elf isoroot/boot/dragkern.elf
	grub-mkrescue isoroot -o dragkern.iso

clean:
	rm -r *.o *.elf *.iso isoroot/* isoroot/

qemu:
	qemu-system-i386 -cdrom dragkern.iso