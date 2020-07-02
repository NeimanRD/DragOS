#include <stdarg.h>
#include <stddef.h>
#include <lib/print.h>
#include <lib/string.h>
#include <lib/stdlib.h>
#include <drivers/tty.h>


int cprintf_internal(v_color_t color, const char *format, va_list args)
{
    char *format_string;
    int no = 0;

    for(; *format != '\0'; format++)
    {
        int format_i;
        if(*format == '%')
        {
            format++;

            switch(*format)
            {
                case 'c' :
                    format_i = va_arg(args, int);
                    putchar(format_i, color);
                    break;
                case 'i' :
                    format_i = va_arg(args, int);
                    if (format_i < 0)
                    {
                        format_i = -format_i;
                        putchar('-', color);
                    }
                    tty_color_write(itoa(format_i, 10), color);
                    break;
                case 'o' :
                    format_i = va_arg(args, int);
                    tty_color_write(itoa(format_i, 8), color);
                    break;
                case 's' :
                    format_string = va_arg(args, char*);
                    tty_color_write(format_string, color);
                    break;
                case '#' :
                    tty_color_write("0x", color);
                    format++;
                    format_i = va_arg(args, unsigned int);
                    tty_color_write(itoa(format_i, 16), color);
                    format++;
                    break;  
                case 'x' :
                    format_i = va_arg(args, unsigned int);
                    tty_color_write(itoa(format_i, 16), color);
                    break;
                default:
                    no = -1;
                    return no;
            }
        } 
        else 
        {
            putchar(*format, color);
        }
    }
    return no;
}
