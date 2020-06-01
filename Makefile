current_dir = $(shell pwd)
export SYSROOT = $(shell pwd)/sysroot

.PHONY: clean qemu iso build

all: build

build:
	cd kernel && $(MAKE) && $(MAKE) install

qemu: iso
	qemu-system-i386 -cdrom redux.iso


iso: build
	mkdir -p iso/boot/grub
	cp $(SYSROOT)/boot/redux.elf iso/boot/redux.kernel
	@echo "menuentry "ReduxOS" {\
        multiboot /boot/redux.kernel\
    }" > grub.cfg 
	cp grub.cfg iso/boot/grub/grub.cfg
	grub-mkrescue -o redux.iso iso

clean:
	cd kernel && $(MAKE) clean
	rm -r sysroot
	rm -r iso

