#include <stddef.h>

static int terminal_row = 0;
static int terminal_column = 0;
static char* const VGA_MEMORY = (char*) 0xB8000;
static const char VGA_COLOR = 0x07;

void putchar(char c) {
    const size_t index = (terminal_row * 80 + terminal_column) * 2;
    VGA_MEMORY[index] = c;
    VGA_MEMORY[index + 1] = VGA_COLOR;

    terminal_column++;
    if (terminal_column >= 80) {
        terminal_column = 0;
        terminal_row++;
    }
}

void print(const char* str) {
    for (size_t i = 0; str[i] != '\0'; i++) {
        putchar(str[i]);
    }
}
