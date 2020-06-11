#ifndef STRING_H
#define STRING_H

#include <stddef.h>

size_t strlen(const char *str);
void *memset(void *dest, int value, size_t len);
void *memcpy(void *dest, const void *src, size_t len);
#endif