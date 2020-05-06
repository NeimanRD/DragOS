# C function 'kernel_main' is in file 'kernel.c'
.extern kernel_main
 
# We declare the 'start' label as global so the linker will know where it is
.global start
 
# Our bootloader, GRUB, needs to know some basic information about our kernel before it can boot it.
.set MB_MAGIC, 0x1BADB002          # This is a 'magic' constant that GRUB will use to detect our kernel's location.
.set MB_FLAGS, (1 << 0) | (1 << 1) # This tells GRUB to 1: load modules on page boundaries and 2: provide a memory map (this is useful later in development)
.set MB_CHECKSUM, (0 - (MB_MAGIC + MB_FLAGS)) # Checksum + magic + flags = 0
 
# We now start the section of the executable that will contain our Multiboot header
.section .multiboot
	.align 4 # Make sure the following data is aligned on a multiple of 4 bytes
	# Use the previously calculated constants in executable code
	.long MB_MAGIC
	.long MB_FLAGS
	# Use the checksum we calculated earlier
	.long MB_CHECKSUM
 
# This section contains data initialised to zeroes when the kernel is loaded
.section .bss
	# Our C code will need a stack to run. Here, we allocate 4096 bytes (or 4 Kilobytes) for our stack.
	# We can expand this later if we want a larger stack. For now, it will be perfectly adequate.
	.align 16
	stack_bottom:
		.skip 4096 # Reserve a 4096-byte (4K) stack
	stack_top:
 
# This section contains our actual assembly code to be run when our kernel loads
.section .text
	start:
		# Set up environment for C
        # x86 stack grows downward
		mov $stack_top, %esp # Set the stack pointer to the top of the stack

		# At this point, we can call our main C function.
		call kernel_main
 
		# If, by some mysterious circumstances, the kernel's C code ever returns, all we want to do is to hang the CPU
		hang:
			cli      # Disable CPU interrupts
			hlt      # Halt the CPU
			jmp hang # If that didn't work, loop around and try again.