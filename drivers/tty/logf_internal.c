#include <drivers/tty/log.h>
#include <drivers/tty/serial.h>
#include <lib/stdlib.h>

int logf_internal(const char *format, va_list args)
{
    char *format_string;
    int format_i;
    int no = 0;

    for(; *format != '\0'; format++)
    {
        if(*format == '%')
        {
            format++;

            switch(*format)
            {
                case 'c' :
                    format_i = va_arg(args, int);
                    serial_putc(format_i);
                    break;
                case 'i' :
                    format_i = va_arg(args, int);
                    if (format_i < 0)
                    {
                        format_i = -format_i;
                        serial_putc('-');
                    }
                    serial_write(itoa(format_i, 10));
                    break;
                case 'o' :
                    format_i = va_arg(args, int);
                    serial_write(itoa(format_i, 8));
                    break;
                case 's' :
                    format_string = va_arg(args, char*);
                    serial_write(format_string);
                    break;
                case '#' :
                    serial_write("0x");
                    format++;
                    format_i = va_arg(args, unsigned int);
                    serial_write(itoa(format_i, 16));
                    format++;
                    break;  
                case 'x' :
                    format_i = va_arg(args, unsigned int);
                    serial_write(itoa(format_i, 16));
                    break;
                default:
                    no = -1;
                    return no;
            }
        } 
        else 
        {
            serial_putc(*format);
        }
    }
    return no;
}