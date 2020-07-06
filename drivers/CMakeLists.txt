add_subdirectory(tty)
target_sources(tinker.kernel PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/timer.c")