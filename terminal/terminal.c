#include <stddef.h>
#include <stdint.h>
#include "terminal.h"

uint8_t combine_colors(enum colors fg, enum colors bg) 
{
	return fg | bg << 4;
}
 
uint16_t combine_text(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_initialize(void) 
{
    main_terminal.row = 0;
    main_terminal.column = 0;
    main_terminal.buffer = (uint16_t*) 0xB8000;
	main_terminal.color = combine_colors(GREEN, BLACK);
	for (int i = 0; i < HEIGHT_T; i++) {
		for (int j = 0; j < WIDTH_T; j++) {
			const size_t index = i * HEIGHT_T + j;
			*(main_terminal.buffer + index) = combine_text(' ', main_terminal.color);
		}
	}
}
 
void insert_at(char c, uint8_t color, unsigned x, unsigned y) 
{
	*(main_terminal.buffer + y * WIDTH_T + x) = combine_text(c, color);
}
void delete_last(unsigned int size){
	for (unsigned int i = 0; i < size; i++) {
		insert_at(' ', main_terminal.color, --main_terminal.column, main_terminal.row);
	}
}