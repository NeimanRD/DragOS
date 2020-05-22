#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <kernel/tty.h>
#include <kernel/vga.h>
#include <libk/string.h>

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_column;

uint8_t terminal_color;
uint16_t *terminal_buffer;

void tty_init(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_color(COLOR_WHITE, COLOR_BLACK);
    terminal_buffer = (uint16_t*) 0xB8000;
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x;
            terminal_buffer[index] = vga_text(' ', terminal_color);
        }
    }

}

void tty_scroll()
{
    //start from row 2
    //loop through each character and subtract VGA_WIDTH from them
    //last row first put in previous row, then fill it with space
}

void tty_put_entry_at(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_text(c, color);
}

void tty_putc(char c)
{
    if ((int)c == 0x0A)
    {
        terminal_row++;
        terminal_column = 0;
        return;
    }
    tty_put_entry_at(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
        {
            terminal_row = 0;
        }
    }
}

void tty_write(const char *str, size_t len)
{
    for (size_t i = 0; i < len; i++)
    {
        tty_putc(str[i]);
    }
}

void tty_write_string(const char* str)
{
    tty_write(str, strlen(str));
}
