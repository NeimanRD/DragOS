current_dir = $(shell pwd)
ARCH = i386
CC = i686-elf-gcc
AS = i686-elf-as
CFLAGS = $(CFLAGS) -Wall -Wextra -Wno-unused-parameter -ffreestanding -fno-builtin -fdiagnostics-color=always
LDFLAGS := $(LDFLAGS) -nostdlib -T $(current_dir)/boot/linker.ld -lgcc

C_FILES = $(wildcard libk/stdio/*.c libk/stdlib/*.c libk/string/*.c modules/*.c *.c)
S_FILES = $(wildcard boot/*.s)
C_OBJECTS = $(C_FILES:.c = .c.o)
S_OBJECTS = $(S_FILES:.s = .s.o)

H_FILES = $(wildcard include/libk/*.h include/modules/*.h)

.PHONY: install

all: redux.kernel

redux.kernel: $(C_OBJECTS) $(S_OBJECTS)
	$(CC) $(LDFLAGS) -o $@ $<

%.c.o: %.c 
	$(CC) $(CFLAGS) -o $@ $<

%.s.o: %.s
	$(AS) -o $@ $<

install: redux.kernel
	mkdir -p $(SYSROOT)/boot/ && mkdir -p $(SYSROOT)/include/
	cp redux.kernel $(SYSROOT)/boot/redux.kernel
	cp -r include/. $(SYSROOT)/include/.

clean:
	rm -r $(C_OBJECTS) $(S_OBJECTS) redux.kernel