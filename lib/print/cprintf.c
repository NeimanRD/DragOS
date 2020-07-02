#include <stdarg.h>
#include <lib/print.h>
#include <drivers/vga.h>

//A minimal implementation of printf but with color options


int cprintf(v_color_t color, const char *format, ...)
{
    va_list arg;
    va_start(arg, format);
    int i = cprintf_internal(color, format, arg);
    va_end(arg);
    return i;
}
