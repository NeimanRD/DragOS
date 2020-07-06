add_subdirectory(tty)
target_sources(solcore.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/timer.c")