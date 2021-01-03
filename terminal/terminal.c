#include <stddef.h>
#include <stdint.h>
#include "../include/terminal.h"
#include "../include/commands.h"
#include "../include/macros.h"
#include "../include/std.h"
#include "../include/threads.h"
#include "../include/keyboard.h"

uint8_t combine_colors(enum colors fg, enum colors bg) {
	return fg | bg << 4;
}
 
uint16_t combine_text(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
void set_bg_col(enum colors col){
	main_terminal.bgcolor = col;
}
void set_fn_col(enum colors col){
	main_terminal.fncolor = col;
}
void mainloop(){
	char line[256] = {0};
	while (1) {
		CMD_LINE		
		scan("%ss", line);
		if (*line) add_line(line);
		if (command(line));
		else print("Invalid sequence '%s'. Type 'help' to see avalible commands.\n", line);
		keyboard.enter = terminal;
		mem_set(line, 0, 256);
	}
}

void terminal_initialize() {
    main_terminal.row = 0;
    main_terminal.column = 0;
    main_terminal.buffer = (uint16_t*)0xB8000;
	main_terminal.backspace_x = 0;
	main_terminal.backspace_y = 0;
	mem_set(main_terminal.lines, 0, 30 * 256);
	main_terminal.lines_counter = 0;
	main_terminal.lines_index = 0;
	set_bg_col(BLACK);
	set_fn_col(LIGHT_GREY);
	main_terminal.color = combine_colors(main_terminal.fncolor, main_terminal.bgcolor);
}

void start_screen(){
	print("\tPetrOS 0.01\t\t");
    datetime_print();
	print("\n\n");
	add_thread((uint32_t)mainloop, "mainloop");
	ENABLE_IRQ
}
void add_line(char *line){
	for (unsigned int i = 0; i <= strlen(line) && i < 256; i++){
		main_terminal.lines[main_terminal.lines_counter][i] = line[i];
	}
	if (main_terminal.lines_counter++ >= 29){
		for (int i = 0;  i < 29; i++){
			for (int j = 0; j < 256; j++){
				main_terminal.lines[i][j] = main_terminal.lines[i + 1][j];
			}
		}
		main_terminal.lines_counter = 29;
	}
	main_terminal.lines_index = main_terminal.lines_counter;
}

void insert_at(char c, unsigned x, unsigned y) {
	main_terminal.color = combine_colors(main_terminal.fncolor, main_terminal.bgcolor);
	*(main_terminal.buffer + y * WIDTH_T + x) = combine_text(c, main_terminal.fncolor);
}

void scroll(){
	for (int i = 0; i <= SCROLL_L * WIDTH_T; i++){
		*(main_terminal.buffer + SCREEN_B - WIDTH_T + i)  = *(main_terminal.buffer + SCREEN_B + i);
	}
	
}