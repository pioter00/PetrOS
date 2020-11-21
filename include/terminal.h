#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>

#define WIDTH_T 80
#define HEIGHT_T 25
#define SCREEN_B (80 * 17)

struct terminal {
    size_t row;
    size_t column;
    uint8_t	bgcolor;
	uint8_t	fncolor;
	uint8_t	color;
    uint16_t *buffer;

	uint8_t caps_flag;
};

struct terminal main_terminal;

enum colors {
	BLACK,
	BLUE,
	GREEN,
	CYAN,
	RED,
	MAGENTA,
	BROWN,
	LIGHT_GREY,
	DARK_GREY,
	LIGHT_BLUE,
	LIGHT_GREEN,
	LIGHT_CYAN,
	LIGHT_RED,
	LIGHT_MAGENTA,
	LIGHT_BROWN,
	WHITE,
};
uint8_t combine_colors(enum colors fg, enum colors bg);
 
uint16_t combine_text(unsigned char uc, uint8_t color);

void terminal_initialize();
 
void insert_at(char c, unsigned x, unsigned y);

void delete_last(unsigned int size);

void set_bg_col(enum colors col);
void set_fn_col(enum colors col);

void scroll();

void kbd_putchar(char c);
void kbd_set(uint8_t code);

#endif