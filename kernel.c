#include <stddef.h>
#include <stdint.h>

#include "libs/std.h"
#include "terminal/terminal.h"

extern struct terminal main_terminal;
void start_kernel(void) 
{
	terminal_initialize();
	print("\tPetrOS 0.01\n\n");
	print("||\\\\\\\\                                  ///|||\\\\\\    ////|\\\\\\\n");
	print("||   \\\\             ||                 ||       ||  ||      \\\\\n");
	print("||    ||            ||                 ||       ||  ||\n");
	print("||    //          \\\\\\\\\\\\               ||       ||   \\\\\n");
	print("||/////    ////\\\\   ||      ///|||\\    ||       ||     \\\\\\\\\n");
	print("||        ||    \\\\  ||     //  ||  \\\\  ||       ||          \\\\\n");
	print("||        ||||||||  ||         ||      ||       ||           ||\n");
	print("||        ||        ||         ||      ||       ||   \\      ||\n");
	print("||         //////    \\\\\\\\      ||       |\\\\\\||///     \\\\|/////\n");

}