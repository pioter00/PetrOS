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

#define CMD_LINE_LEN 13
#define ENABLE_IRQ __asm__ __volatile__ ("sti");
#define DISABLE_IRQ __asm__ __volatile__ ("cli");


#endif