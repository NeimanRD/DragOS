target_sources(solcore.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/printf.c"
                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/putchar.c"
                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/puts.c"
                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cprintf.c"
                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cprintf_internal.c")