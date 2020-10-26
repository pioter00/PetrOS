#include <stddef.h>
#include <stdint.h>

#include "libs/std.h"
#include "terminal/terminal.h"
#include "libs/std.c"
#include "terminal/terminal.c"
struct terminal main_terminal;
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
	for (int i = 1; i < 100; i++){
		printf("%d ", i);
	}
}
// gcc -m32 -O2 -fno-pie -fno-builtin -fomit-frame-pointer -c kernel.c -o libs/std.c -o teminal/terminal.c -o kernel.o