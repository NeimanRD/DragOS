#include <lib/string.h>

void *memset(void *dest, int value, size_t len)
{
    unsigned char *ptr = dest;
    while (len-- > 0)
    {
        *ptr++ = value;
    }
    return dest;
}
