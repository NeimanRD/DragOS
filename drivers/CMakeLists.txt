target_sources(spazv1.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/io.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/tty.c"
                             PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/cursor.c")