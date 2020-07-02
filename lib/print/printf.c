#include <stdarg.h>
#include <lib/print.h>
#include <drivers/vga.h>

//A minimal implementation of printf


int printf(const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    int i = cprintf_internal(COLOR_WHITE, format, arg);
    va_end(arg);
    return i;
}
