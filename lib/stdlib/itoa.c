#include <lib/stdlib.h>

char *itoa(int num, int base)
{
    char *ptr;
    char representation[] = "0123456789ABCDEF";
    char buf[50];
    
    ptr = &buf[49];
    *ptr = '\0';

    do
    {
        *--ptr = representation[num % base];
        num /= base;
    } while (num != 0);

    return ptr;
}