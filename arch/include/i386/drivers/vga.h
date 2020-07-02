#ifndef VGA_H
#define VGA_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

extern const size_t VGA_WIDTH;
extern const size_t VGA_HEIGHT;

typedef enum vga_color
{
    COLOR_BLACK = 0,
    COLOR_BLUE = 1,
    COLOR_GREEN = 2,
    COLOR_CYAN = 3,
    COLOR_RED = 4,
    COLOR_MAGENTA = 5,
    COLOR_BROWN = 6,
    COLOR_LIGHT_GRAY = 7,
    COLOR_DARK_GRAY = 8,
    COLOR_LIGHT_BLUE = 9,
    COLOR_LIGHT_GREEN = 10,
    COLOR_LIGHT_CYAN = 11,
    COLOR_LIGHT_RED = 12,
    COLOR_LIGHT_MAGENTA = 13,
    COLOR_YELLO = 14,
    COLOR_WHITE = 15
} v_color_t;

static inline uint8_t vga_color(v_color_t fg, v_color_t bg)
{
    return (fg | bg << 4);
}

static inline uint16_t vga_text(unsigned char c, uint8_t color)
{
    return (uint16_t)(c | color << 8);
}


#endif