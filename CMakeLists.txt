cmake_minimum_required(VERSION 3.12)
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

set(COMPILER_NAME "i686-elf")
set(arch "i386")

find_program(CMAKE_C_COMPILER "${COMPILER_NAME}-gcc")
if(NOT CMAKE_C_COMPILER)
    message(FATAL_ERROR "i686-elf cross-compiler not found!")
endif(NOT CMAKE_C_COMPILER)
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_ASM-ATT_COMPILER "${COMPILER_NAME}-as")
set(SYSROOT "${CMAKE_CURRENT_SOURCE_DIR}/sysroot")
set(BOOT "/boot")
set(USR "/usr")
set(INCLUDE "/include")

project(ReduxOS VERSION 1.0 LANGUAGES C)
enable_language(ASM-ATT)
add_executable(redux.kernel)
add_subdirectory(kernel)

if(EXISTS "${SYSROOT}")
    file(REMOVE_RECURSE "${SYSROOT}")
endif(EXISTS "${SYSROOT}")
install(TARGETS redux.kernel DESTINATION "${SYSROOT}${BOOT}")

install(DIRECTORY "${KERNEL_INCLUDE_DIR}" DESTINATION "${SYSROOT}${USR}${INCLUDE}/kernel/")