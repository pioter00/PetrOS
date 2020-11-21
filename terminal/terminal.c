#include <stddef.h>
#include <stdint.h>
#include "../include/terminal.h"
#include "../include/macros.h"
#include "../include/std.h"

uint8_t combine_colors(enum colors fg, enum colors bg) 
{
	return fg | bg << 4;
}
 
uint16_t combine_text(unsigned char uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}
void set_bg_col(enum colors col){
	main_terminal.bgcolor = col;
}
void set_fn_col(enum colors col){
	main_terminal.fncolor = col;
}
void terminal_initialize(void) 
{
    main_terminal.row = 0;
    main_terminal.column = 0;
    main_terminal.buffer = (uint16_t*) 0xB8000;
	main_terminal.nl_flag = 1;
	set_bg_col(BLACK);
	set_fn_col(LIGHT_GREY);
	main_terminal.color = combine_colors(main_terminal.fncolor, main_terminal.bgcolor);
}
 
void insert_at(char c, unsigned x, unsigned y) 
{
	main_terminal.color = combine_colors(main_terminal.fncolor, main_terminal.bgcolor);
	*(main_terminal.buffer + y * WIDTH_T + x) = combine_text(c, main_terminal.fncolor);
}

void scroll(){
	for (int i = 0; i < 640; i++){
		*(main_terminal.buffer + SCREEN_B - WIDTH_T + i)  = *(main_terminal.buffer + SCREEN_B + i);
	}
	
}