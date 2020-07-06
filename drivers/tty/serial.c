#include <drivers/io.h>
#include <drivers/tty/serial.h>
#include <stddef.h>
#include <lib/string.h>

const uint16_t COM1 = 0x3F8;

void serial_putc(const char c)
{
    outb(COM1, c);
}

int serial_write_string(const char *data, size_t size)
{
    unsigned int written = 0;

    while (size--)
    {
        serial_putc(data[written++]);
    }
    
    return written;
}

int serial_write(const char *data)
{
    int i = serial_write_string(data, strlen(data));
    return i;
}