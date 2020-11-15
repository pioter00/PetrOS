#include <stddef.h>
#include <stdint.h>
#include "libs/std.h"
#include "libs/asm.h"
#include "libs/timer.h"
#include "terminal/terminal.h"

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
	set_fn_col(LIGHT_GREY);
	print("\n");
	set_fn_col(GREEN);
	print("command");
	set_fn_col(LIGHT_GREY);
	print(">\n");
	
}