#ifndef LOG_H
#define LOG_H

#include <stddef.h>
#include <stdarg.h>

typedef enum log_type
{
    cpu,
    mm,
    tty,
    device,
    warning,
    error, 
} logtype_t;

extern char *logtype_string[];

int logf(logtype_t type, const char *format, ...);
int logf_internal(const char *format, va_list args);

#endif