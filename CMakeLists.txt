cmake_minimum_required(VERSION 3.12)
set(CMAKE_SYSTEM_NAME Generic)

if(WIN32)
    if(CYGWIN)
        message(FATAL_ERROR "No Cygwin Detected!")
    endif(CYGWIN)
endif(WIN32)

set(SYSROOT "${CMAKE_CURRENT_SOURCE_DIR}/sysroot")


set(ARCH "i386")
if("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")
    message(FATAL_ERROR "In-source builds are not allowed!")
endif("${CMAKE_SOURCE_DIR}" STREQUAL "${CMAKE_BINARY_DIR}")

set(COMPILER_NAME "i686-elf")

find_program(CMAKE_ASM_NASM_COMPILER "nasm")
set(CMAKE_ASM_NASM_OBJECT_FORMAT elf32)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wno-unused-parameter -ffreestanding -fno-builtin -fdiagnostics-color=always")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -T ${CMAKE_CURRENT_SOURCE_DIR}/arch/${ARCH}/boot/linker.ld")

set(ARCH_PATH "${CMAKE_SOURCE_DIR}/arch/${ARCH}")

find_program(CMAKE_C_COMPILER "${COMPILER_NAME}-gcc")
if(NOT CMAKE_C_COMPILER)
message(FATAL_ERROR "i686-elf cross-compiler not found!")
endif(NOT CMAKE_C_COMPILER)
set(CMAKE_C_COMPILER_WORKS 1)

project(solcore VERSION 0.0.1 LANGUAGES C)
enable_language(ASM_NASM)
add_executable(solcore.kernel)
target_link_libraries(solcore.kernel gcc)
target_include_directories(solcore.kernel PRIVATE include)
add_subdirectory(arch)
add_subdirectory(drivers)
add_subdirectory(lib)
add_subdirectory(kernel)

set(KERNEL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")

install(TARGETS solcore.kernel DESTINATION "${SYSROOT}${BOOT}")
