#include <stddef.h>
#include <stdint.h>
#include "libs/std.h"
#include "terminal/terminal.h"

void start_kernel(void) 
{ 
	terminal_initialize();
	printf("\tPetrOS 0.01\n\n");
	printf("||\\\\\\\\                                  ///|||\\\\\\    ////|\\\\\\\n");
	printf("||   \\\\             ||                 ||       ||  ||      \\\\\n");
	printf("||    ||            ||                 ||       ||  ||\n");
	printf("||    //          \\\\\\\\\\\\               ||       ||   \\\\\n");
	printf("||/////    ////\\\\   ||      ///|||\\    ||       ||     \\\\\\\\\n");
	printf("||        ||    \\\\  ||     //  ||  \\\\  ||       ||          \\\\\n");
	printf("||        ||||||||  ||         ||      ||       ||           ||\n");
	printf("||        ||        ||         ||      ||       ||   \\      ||\n");
	printf("||         //////    \\\\\\\\      ||       |\\\\\\||///     \\\\|/////\n");
}
