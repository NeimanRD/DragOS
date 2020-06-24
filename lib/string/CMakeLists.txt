target_sources(solcore.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/memcpy.c"
                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/memset.c"
                            PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/strlen.c")