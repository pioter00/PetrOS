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
	main_terminal.caps_flag = 0;
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
void delete_last(unsigned int size){
	for (unsigned int i = 0; i < size; i++) {
		insert_at(' ', --main_terminal.column, main_terminal.row);
	}
}
void kbd_putchar(char c){
	if (c == '\n') {
		main_terminal.row++;
		main_terminal.column = 0;
		CMD_LINE
	}
	else if (c == '\t') {
		main_terminal.column += 4;
	}
  	else if (c == '\b' && main_terminal.column == 0) {
		main_terminal.row--;
		main_terminal.column = 79;
		insert_at(' ', 79, main_terminal.row);
	}
  	else if (c == '\b' && main_terminal.column > 0) {
		if (main_terminal.column > CMD_LINE_LEN)
    		insert_at(' ', --main_terminal.column, main_terminal.row);
	}
  	else if (c == 0){

  	}
	else {
		if (main_terminal.caps_flag == 1 && c >= 'a' && c <= 'z') insert_at(c - 32, main_terminal.column, main_terminal.row);
		else insert_at(c, main_terminal.column, main_terminal.row);
		main_terminal.column++;
  	} 
	if (main_terminal.column == WIDTH_T){
		main_terminal.column = 0;
		main_terminal.row++;
  	} 
	if (main_terminal.row == HEIGHT_T){
    scroll();
    main_terminal.row = HEIGHT_T - 1;
    for (int i = 0; i < WIDTH_T; i++) {
      insert_at(' ', main_terminal.column + i, main_terminal.row);
    }
  }
  move_csr(); 
}
void kbd_set(uint8_t code){
	if (code == 58 && main_terminal.caps_flag == 0) main_terminal.caps_flag = 1;
	else if (code == 58 && main_terminal.caps_flag == 1) main_terminal.caps_flag = 0;
	// print(" [%d] cps: %d ", code, main_terminal.caps_flag);
}