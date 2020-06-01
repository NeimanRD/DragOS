#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <modules/tty.h>
#include <modules/vga.h>
#include <libk/string.h>

/* Set size of buffer */
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
    terminal_buffer = (uint16_t*) 0xB8000; // memory location for VGA text buffer
    for (size_t y = 0; y < VGA_HEIGHT; y++)
    {
        for (size_t x = 0; x < VGA_WIDTH; x++)
        {
            const size_t index = y * VGA_WIDTH + x; /* Since the buffer is linear, calculate using this */
            terminal_buffer[index] = vga_text(' ', terminal_color); // sets each screen character to a space with the set background
        }
    }

}

void tty_scroll() 
{
    /* How scrolling works:
    Copy the value in each location in the buffer, 
    then copy that to the location above it
    After we finish copying the last row, fill it with spaces
    */
    terminal_column = 0;
    for (size_t y = 1; y < VGA_HEIGHT; y++) /* Start at row 2 */
    {
        const size_t target_row_index = (y - 1) * VGA_WIDTH;
        const size_t current_row_index = y * VGA_WIDTH;
        memcpy(&terminal_buffer[target_row_index], &terminal_buffer[current_row_index], 2 * VGA_WIDTH);
    }
    for (size_t x = 0; x < VGA_WIDTH; x++)
    {
        const size_t target_index = (VGA_HEIGHT - 1) * VGA_WIDTH + x;
        terminal_buffer[target_index] = vga_text(' ', terminal_color); /* Fill last row with space */
    }
}

void tty_put_entry_at(unsigned char c, uint8_t color, size_t x, size_t y)
{
    const size_t index = y * VGA_WIDTH + x;
    terminal_buffer[index] = vga_text(c, color);
}

void tty_putc(char c)
{
    if (c == '\n')
    {
        terminal_row++;
        terminal_column = 0;
    }
    else
    {
        tty_put_entry_at(c, terminal_color, terminal_column, terminal_row);
        if (++terminal_column == VGA_WIDTH)
        {
            terminal_column = 0;
            terminal_row++;
        }
    }
    if (terminal_row == VGA_HEIGHT)
    {
        tty_scroll();
        terminal_row = VGA_HEIGHT - 1;
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
