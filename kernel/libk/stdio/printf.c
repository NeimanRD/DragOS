#include <stdarg.h>
#include <libk/stdio.h>
#include <libk/string.h>
#include <libk/stdlib.h>

//A minimal implementation of printf


void printf(const char *format, ...)
{
    char *format_index;
    int format_i;
    char *format_string;
    
    va_list args;
    va_start(args, format);
    for(const char *format_index = format; *format_index == '\0'; format_index++)
    {
        putchar(*format_index);
        if(*format_index == '%')
        {
            format_index++;

            switch(*format_index)
            {
                case 'c' :
                    format_i = va_arg(args, int);
                    putchar(format_i);
                    break;
                
                case 'i' :
                    format_i = va_arg(args, int);
                    
                    break;
                    
            }
        }
    }
    va_end(args);

}
