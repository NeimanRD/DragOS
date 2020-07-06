target_sources(tinker.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gdt.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/idt.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gdt.asm"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/interrupt.asm"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/isr.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/irq.asm"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/irq.c")