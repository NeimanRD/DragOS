cmake_minimum_required(VERSION 3.17)
set(CMAKE_SYSTEM_NAME Generic)

if(WIN32)
    if(CYGWIN)
        message(FATAL_ERROR "No Cygwin Detected!")
    endif(CYGWIN)
endif(WIN32)


if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed!")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

set(CMAKE_ASM-ATT_COMPILE_OBJECT "${CMAKE_ASM-ATT_COMPILE_OBJECT} -ffreestanding -g")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -ffreestanding -fno-builtin -fdiagnostics-color=always")

set(COMPILER_NAME "i686-elf-gcc")
set(arch "i386")

find_program(CMAKE_C_COMPILER COMPILER_NAME)
if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "Cross-compiler not found for arch i386!")
endif(NOT CMAKE_C_COMPILER)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_ASM-ATT_COMPILER)

project(DragOS C)
enable_language(ASM-ATT)
add_executable(dragos.kernel)
add_subdirectory(kernel)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/sysroot/")
    file(REMOVE_RECURSE "${CMAKE_CURRENT_SOURCE_DIR}/sysroot/")
endif()
install(TARGETS dragos.kernel DESTINATION "${CMAKE_SOURCE_DIR}/sysroot/boot/")

install(DIRECTORY "${KERNEL_INCLUDE_DIR}" DESTINATION "${CMAKE_SOURCE_DIR}/sysroot/usr/include/kernel/")



