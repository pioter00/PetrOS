#include <stddef.h>
#include <stdint.h>
#include "include/std.h"
#include "include/timer.h"
#include "include/terminal.h"

char *user = "pjoter";

void start_kernel(void) 
{
	terminal_initialize();
	print("\tPetrOS 0.01\n\n");
	set_fn_col(DARK_GREY);
	for(int i = 0; i < WIDTH_T; i++){
		print("=");
	}
	set_fn_col(GREEN);
	print("\n");
	print("        ||\\\\\\\\                                  ///|||\\\\\\    ////|\\\\\\\n");
	print("        ||   \\\\             ||                 ||       ||  ||      \\\\\n");
	print("        ||    ||            ||                 ||       ||  ||\n");
	print("        ||    //          \\\\\\\\\\\\               ||       ||   \\\\\n");
	print("        ||/////    ////\\\\   ||      ///|||\\    ||       ||     \\\\\\\\\n");
	print("        ||        ||    \\\\  ||     //  ||  \\\\  ||       ||          \\\\\n");
	print("        ||        ||||||||  ||         ||      ||       ||           ||\n");
	print("        ||        ||        ||         ||      ||       ||   \\      ||\n");
	print("        ||         //////    \\\\\\\\      ||       |\\\\\\||///     \\\\|/////\n\n");
	set_fn_col(DARK_GREY);
	for(int i = 0; i < WIDTH_T; i++){
		print("=");
	}
	print("\n");

	set_fn_col(BLUE);
	print("%s", user);
	set_fn_col(LIGHT_GREY);
	print("$");
	set_fn_col(GREEN);
	print("home");
	set_fn_col(LIGHT_GREY);
	print("> ");
	
}