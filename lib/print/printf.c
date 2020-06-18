#include <stdarg.h>
#include <stddef.h>
#include <lib/print.h>
#include <lib/string.h>
#include <lib/stdlib.h>

//A minimal implementation of printf


void printf(const char *format, ...)
{
    int format_i;
    char *format_string;
    
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
                case 'o' :
                    format_i = va_arg(args, int);
                    puts(itoa(format_i, 8));
                    break;
                case 's' :
                    format_string = va_arg(args, char*);
                    puts(format_string);
                    break;
                case '#' :
                    puts("0x");
                    format++;
                    format_i = va_arg(args, unsigned int);
                    puts(itoa(format_i, 16));
                    format++;
                    break;  
                case 'x' :
                    format_i = va_arg(args, unsigned int);
                    puts(itoa(format_i, 16));
                    break;
            }
        } else {
            putchar(*format);
        }
    }
    va_end(args);

}
