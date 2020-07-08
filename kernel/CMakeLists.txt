target_sources(tinker.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/kmain.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/elf.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/panic.c")