target_sources(spazv1.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gdt.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/idt.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/gdt.s"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/interrupt.s"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/isr.c")