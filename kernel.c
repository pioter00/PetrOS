#include <stddef.h>
#include <stdint.h>
#include "include/gdt.h"
#include "include/idt.h"
#include "include/isr.h"
#include "include/irq.h"
#include "include/keyboard.h"
#include "include/std.h"
#include "include/timer.h"
#include "include/terminal.h"
#include "include/macros.h"

int read_vector(int* vec, int size, int stop_value)
{
  int i,v,counter=0;
  if (size<1 || vec == NULL) return -1;
  for (i=0;i<size;i++)
  {
    v = scan("%d", (vec + i));
	if (!v) return -2;
    if (*(vec + i) == stop_value) break;
    counter++;
  }
  return counter;
}
int sort_vector(int* arr, int n)
{
	if (n<1) return 1;
	int i, j,s; 
	for (i = 0; i < n-1; i++) 
		for (j = 0; j < n-i-1; j++)  
			if (arr[j] > arr[j+1])
			{
				s = arr[j];
				arr[j] = arr[j+1];
				arr[j+1]= s;
			}
  return 0;
}

void display_vector(const int* vec, int size)
{
  int i;
  for (i=0;i<size;i++)
  {
    print("%d ", *(vec + i));
  }
  print("\n");
}

int program(){
	int vec[100];
	print("Enter numbers: ");
	int s = read_vector(vec, 100, 0);
	if (s < 0){
		print("Incorrect input data!\n");
		return s;
	}
	display_vector(vec, s);
	sort_vector(vec, s);
	print("Sorted array: \n");
	display_vector(vec, s);
	return 0;
}

char line[256] = {0};

char *commands[] = {
	"run",
	"echo",
	"help",
	"settime",
	NULL
};

void _run(){
	int err_code = program();
	print("returned value from program: %d\n", err_code);
	flush();
}
void _echo(char * str){
	print("%s\n", str);
}
void _help(){
	print("Avalible commands:\n");
	for (int i = 0; *(commands + i); i++){
		print("%s\n", *(commands + i));
	}	
}
int command(char *str) {
	if (*str == 0) return 1;
	if (*str == 'r' && *(str + 1) == 'u' && *(str + 2) == 'n'){
		_run();
		return 1;
	}
	else if (*str == 'e' && *(str + 1) == 'c' && *(str + 2) == 'h' && *(str + 3) == 'o'){
		_echo(str + 5);
		return 1;
	}
	else if (*str == 'h' && *(str + 1) == 'e' && *(str + 2) == 'l' && *(str + 3) == 'p'){
		_help();
		return 1;
	}
	return 0;
}
void main() 
{
	gdt_install();
	idt_install();
	isrs_install();
	irq_install();
	terminal_initialize();
	datetime_install();
	keyboard_install();
	ENABLE_IRQ
	print("\tPetrOS 0.01\t\t\t");
    datetime_print();
	print("\n\n");
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
	int err_code;
	while (1)
	{
		CMD_LINE
		scan("%ss", line);
		if (command(line));
		else print("Invalid sequence '%s'. Type 'help' to see avalible commands.\n", line);
	
	}
}