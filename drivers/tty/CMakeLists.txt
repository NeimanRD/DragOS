target_sources(tinker.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/serial.c"
                              PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/logf.c"
                              PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/logf_internal.c")