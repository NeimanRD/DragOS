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
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -nostdlib -T ${CMAKE_CURRENT_SOURCE_DIR}/boot/linker.ld")

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

project(spazv1 VERSION 1.0 LANGUAGES C)
enable_language(ASM-ATT)
add_executable(spazv1.kernel)
target_link_libraries(spazv1.kernel gcc)
target_include_directories(spazv1.kernel PRIVATE include)
add_subdirectory(drivers)
add_subdirectory(lib)
add_subdirectory(boot)
add_subdirectory(kernel)

set(KERNEL_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")

install(TARGETS spazv1.kernel DESTINATION "${SYSROOT}${BOOT}")

install(DIRECTORY "${KERNEL_INCLUDE_DIR}" DESTINATION "${SYSROOT}${USR}${INCLUDE}/kernel/")