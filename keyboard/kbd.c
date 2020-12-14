#include "../include/keyboard.h"
#include "../include/macros.h"
#include "../include/threads.h"
#include "../include/terminal.h"
#include "../include/isr.h"
#include "../include/irq.h"
#include "../include/std.h"
#include <stdint.h>

unsigned char key_map[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',		/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,					/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
unsigned char shift_key_map[128] = 
     { 
  0, '~', '!', '@', '#', '$', '%', '^', 
  '&', '*', '(', ')', '_', '+', '\b', '\t', 
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 
  'O', 'P', '{', '}', '\n', 0, 'A', 'S', 
  'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', 
  '"', '~', 0, '|', 'Z', 'X', 'C', 'V', 
  'B', 'N', 'M', '<', '>', '?', 0, 0, 
  0, 
  ' ',
  0,	/* Caps lock */
  0,	/* 59 - F1 key ... > */
  0,   0,   0,   0,   0,   0,   0,   0,
  0,	/* < ... F10 */
  0,	/* 69 - Num lock*/
  0,	/* Scroll Lock */
  0,	/* Home key */
  0,	/* Up Arrow */
  0,	/* Page Up */
  '-',
  0,	/* Left Arrow */
  0,
  0,	/* Right Arrow */
  '+',
  0,	/* 79 - End key*/
  0,	/* Down Arrow */
  0,	/* Page Down */
  0,	/* Insert Key */
  0,	/* Delete Key */
  0,   0,   0,
  0,	/* F11 Key */
  0,	/* F12 Key */
  0,	/* All other keys are undefined */
};

void arrow_handler(uint8_t scancode){
  uint8_t x = main_terminal.backspace_x;
  uint8_t y = main_terminal.backspace_y;
  if (main_terminal.lines_index > 0 && scancode == 72)
  {
    while (1) {
      if (main_terminal.row == y && main_terminal.column == x) break;
      putch('\b');
      buf_putch('\b');
    }
    for (uint8_t i = 0; i < strlen(main_terminal.lines[main_terminal.lines_index - 1]); i++){
      kbd_putchar(main_terminal.lines[main_terminal.lines_index - 1][i]);
      buf_putch(main_terminal.lines[main_terminal.lines_index - 1][i]);
    }
    if (main_terminal.lines_index > 1) main_terminal.lines_index--;
  }
  else if (main_terminal.lines_index < main_terminal.lines_counter && main_terminal.lines_index >= 0 && scancode == 80){

    while (1) {
      if (main_terminal.row == y && main_terminal.column == x) break;
      putch('\b');
      buf_putch('\b');
    }
    // print(" i: %d s: %d ", main_terminal.lines_index, main_terminal.lines_counter);
    for (uint8_t i = 0; i < strlen(main_terminal.lines[main_terminal.lines_index]); i++){
      kbd_putchar(main_terminal.lines[main_terminal.lines_index][i]);
      buf_putch(main_terminal.lines[main_terminal.lines_index][i]);
    }
    if (main_terminal.lines_index < main_terminal.lines_counter - 1) main_terminal.lines_index++;
  }
}

void keyboard_handler(struct regs *r) {
    unsigned char scancode = inportb(0x60);
    kbd_set(scancode);
    if (scancode < 128) {
      if (keyboard.enter == terminal) {
          arrow_handler(scancode);
      }
      if (keyboard.shift_flag == 1 || keyboard.caps_flag == 1) {
          kbd_putchar(shift_key_map[scancode]);
          if (shift_key_map[scancode]) buf_putch(shift_key_map[scancode]);
      }
      if (keyboard.ctrl_flag == 1 && key_map[scancode] == 'l'){
        mutex_lock();
        return;
      }
      if (keyboard.ctrl_flag == 1 && key_map[scancode] == 'r'){
        mutex_relase();
        return;
      }
      else {
        kbd_putchar(key_map[scancode]);
        if (key_map[scancode]) buf_putch(key_map[scancode]);
      }
    }
}

char buf[KBD_BUF] = {0};

void keyboard_install() {
	keyboard.caps_flag = 0;
	keyboard.shift_flag = 0;
	keyboard.ctrl_flag = 0;
	keyboard.alt_flag = 0;
	keyboard.enter = terminal;
	keyboard.buffer.txt = buf;
	keyboard.buffer.index = 0;
	keyboard.buffer.size = 0;
	irq_install_handler(1, keyboard_handler);
}

void kbd_putchar(char c){
	if (c == '\n') {
    main_terminal.column = 79;
    SET_BCSP_BLOCK
		main_terminal.row++;
		main_terminal.column = 0;
	}
	else if (c == '\t') {
		main_terminal.column += 4;
	}
	else if (c == '\b' && main_terminal.column == 0) {
    int a = main_terminal.column, b = main_terminal.row, c= main_terminal.backspace_x, d = main_terminal.backspace_y;
    // print("tx: %d ty: %d x: %d y: %d\n", main_terminal.column, main_terminal.row, main_terminal.backspace_x, main_terminal.backspace_y);
		if (main_terminal.row > main_terminal.backspace_y && main_terminal.backspace_x != 79){
      main_terminal.row--;
      main_terminal.column = 79;
      insert_at(' ', 79, main_terminal.row);
    }
    // print(" tx: %d ty: %d x: %d y: %d\n", a, b, c, d);
    
	}
	else if (c == '\b' && main_terminal.column > 0) {
	  	// print("tx: %d ty: %d x: %d y: %d\n", main_terminal.column, main_terminal.row, main_terminal.backspace_x, main_terminal.backspace_y);
		if (main_terminal.column > main_terminal.backspace_x && main_terminal.backspace_x < 79 && main_terminal.row == main_terminal.backspace_y)
    		insert_at(' ', --main_terminal.column, main_terminal.row);
    else if (main_terminal.backspace_x == 79) {
      insert_at(' ', --main_terminal.column <= 0 ? 0 : main_terminal.column, main_terminal.row);
    }
		else if (main_terminal.row > main_terminal.backspace_y)
			insert_at(' ', --main_terminal.column, main_terminal.row);
	}

	else if (c == 0){

	}
	else {
		if (keyboard.caps_flag == 1 && c >= 'a' && c <= 'z') insert_at(c - 32, main_terminal.column, main_terminal.row);
		else insert_at(c, main_terminal.column, main_terminal.row);
		main_terminal.column++;
  }

	if (main_terminal.column >= WIDTH_T){
		main_terminal.column = 0;
		main_terminal.row++;
  } 
	if (main_terminal.row >= HEIGHT_T){
    scroll();
    main_terminal.row = HEIGHT_T - 1;
    for (int i = 0; i < WIDTH_T; i++) {
      insert_at(' ', main_terminal.column + i, main_terminal.row);
    }
  }
  move_csr(); 
}
void kbd_set(uint8_t code){
	if (code == 58 && keyboard.caps_flag == 0) keyboard.caps_flag = 1;
	else if (code == 58 && keyboard.caps_flag == 1) keyboard.caps_flag = 0;
	if (code == 42 || code == 54) keyboard.shift_flag = 1;
	else if (code == 170 || code == 182) keyboard.shift_flag = 0;
  else if (code == 29) keyboard.ctrl_flag = 1;
  else if (code == 157) keyboard.ctrl_flag = 0;
}

