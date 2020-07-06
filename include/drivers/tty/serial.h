#ifndef SERIAL_H
#define SERIAL_H

#include <stddef.h>

int serial_write_string(const char *data, size_t size);
void serial_putc(const char c);
int serial_write(const char *data);

#endif