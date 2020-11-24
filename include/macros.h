#ifndef MACROS_H
#define MACROS_H

#define CMD_LINE\
	set_fn_col(GREEN);\
	print("%s", "pjoter");\
	set_fn_col(LIGHT_GREY);\
	print("$");\
	set_fn_col(BLUE);\
	print("home");\
	set_fn_col(LIGHT_GREY);\
	print("> ");\

#define SET_BCSP_BLOCK\
	main_terminal.backspace_x = main_terminal.column;\
	main_terminal.backspace_y = main_terminal.row;\

#define ENABLE_IRQ __asm__ __volatile__ ("sti");
#define DISABLE_IRQ __asm__ __volatile__ ("cli");


#endif