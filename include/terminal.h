#ifndef TERMINAL_H
#define TERMINAL_H

#include <stddef.h>
#include <stdint.h>
#define WIDTH_T 80
#define HEIGHT_T 25
#define SCROLL_L 22
#define SCREEN_B (WIDTH_T * (HEIGHT_T - SCROLL_L))

struct terminal {
    size_t row;
    size_t column;
    uint8_t	bgcolor;
	uint8_t	fncolor;
	uint8_t	color;
    uint16_t *buffer;

	uint8_t backspace_x;
	uint8_t backspace_y;
	char lines[30][256];
	uint8_t lines_index;
	uint8_t lines_counter;
} main_terminal;

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
void start_screen();

void insert_at(char c, unsigned x, unsigned y);

void add_line(char *line);

void test_line(int num);

void set_bg_col(enum colors col);
void set_fn_col(enum colors col);

void scroll();

#endif