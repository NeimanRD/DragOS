#include <stdarg.h>
#include <libk/stdio.h>
#include <libk/string.h>
#include <libk/stdlib.h>

//A minimal implementation of printf


void printf(const char *format, ...)
{
    int format_i;
    
    va_list args;
    va_start(args, format);
    for(; *format != '\0'; format++)
    {
        if(*format == '%')
        {
            format++;

            switch(*format)
            {
                case 'c' :
                    format_i = va_arg(args, int);
                    putchar(format_i);
                    break;
                
                case 'i' :
                    format_i = va_arg(args, int);
                    puts(itoa(format_i, 10));
                    break;
                    
            }
            format++;
        }
        putchar(*format);
    }
    va_end(args);

}
