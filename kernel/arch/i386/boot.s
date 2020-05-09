.set ALIGN, 1 << 0
.set MEMINFO, 1 << 1
.set MAGIC, 0x1BADB002
.set FLAGS, ALIGN | MEMINFO
.set CHECKSUM, (0 - (MAGIC + FLAGS))

.section .multiboot
    .align 4
    .long MAGIC
    .long FLAGS
    .long CHECKSUM

.section .bss
    .align 16
    stackbottom:
        .skip 16384
    stacktop:

.section .text
    .global _start

    _start:
        mov $stacktop, %esp
        call kernel_main

        cli
        loop:
            hlt
            jmp loop