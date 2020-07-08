#include <drivers/tty/log.h>
#include <drivers/tty/serial.h>

char *logtype_string[] = {
    "cpu",
    "mm",
    "tty",
    "device",
    "kernel",
    "warning",
    "error"
};

int logf(logtype_t type, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    for (unsigned int j = 0; j < (sizeof(logtype_string) / sizeof(logtype_string[0])); j++)
    {
        if (j == type)
        {
            serial_write("[");
            serial_write(logtype_string[j]);
            serial_write("] ");
        }
    }
    int i = logf_internal(format, args);
    va_end(args);
    return i;
}