#include <stdint.h>

#include "../include/threads.h"
#include "../include/terminal.h"
#include "../include/std.h"
#include "../include/macros.h"
#include "../include/cmos.h"
#include "../include/timer.h"
#include "../include/keyboard.h"

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



char *commands[] = {
	"- run",
	"- echo",
	"- help",
	"- settime",
	"- clear",
	"- timer",
	"- threads",
	"- kill",
	NULL
};

void _run(){
	int err_code = program();
	print("returned value from program: %d\n", err_code);
	flush();
}

void _clear(){
	mem_set(main_terminal.buffer + WIDTH_T * 2, 0, WIDTH_T * (WIDTH_T - 2) * 2);
	main_terminal.column = 0;
	main_terminal.row = 2;
	move_csr();
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

int checkdate(int day, int month, int year){
	if (day == 31 && (month == 2 || month == 4 || month == 6 || month == 9 || month == 11)) return 1;
	if (day == 30 && month == 2) return 1;
	if (year % 4 != 0 && month == 2) return 1;
	return 0;
}

void _settime(){
	int day, month, year, hour, minutes, seconds;
	print("Set day: ");
	scan("%d", &day);
	if (day < 1 || day > 31){
		print("Invalid value!\n");
		return;
	} 
	print("Set month: ");
	scan("%d", &month);
	if (month < 1 || month > 12){
		print("Invalid value!\n");
		return;
	} 
	print("Set year: ");
	scan("%d", &year);
	if (year < 2000 || year > 3000){
		print("Invalid value!\n");
		return;
	} 
	print("Set hour: ");
	scan("%d", &hour);
	if (hour < 0 || hour > 23){
		print("Invalid value!\n");
		return;
	} 
	print("Set minutes: ");
	scan("%d", &minutes);
	if (minutes < 0 || minutes > 59){
		print("Invalid value!\n");
		return;
	} 
	print("Set seconds: ");
	scan("%d", &seconds);
	if (seconds < 0 || seconds > 59){
		print("Invalid value!\n");
		return;
	}
	if (checkdate(day, month, year)){
		print("Invalid value!\n");
		return;
	}
	DISABLE_IRQ
	write_full_date(day, month, year % 100, hour, minutes, seconds);
	ENABLE_IRQ
}
uint32_t timer_y = 0, timer_ms = 0;

void _timer(void){
	int timer_tick2 = 0;
	DISABLE_IRQ
	uint32_t y = timer_y, ms = timer_ms;
	ENABLE_IRQ
	while (1){
		block_scheduler();
		int temp_y = main_terminal.row;
		int temp_x = main_terminal.column;
		main_terminal.row = y;
   		main_terminal.column = 70;
		printint_at_date(timer_tick2++);
		main_terminal.row = temp_y;
		main_terminal.column = temp_x;
		m = 0;
		unlock_scheduler();
		sleep(ms);
	}
}
void _kill(uint32_t id){
    if (id > threads_control.active_threads || id == 0) return;
    threads_control.thread[id].state = THREAD_TERMINATED;
	threads_control.active_threads--;
    scheduler();
}
void _term(void){
	int timer_tick2 = 0;
	
	DISABLE_IRQ
	uint32_t y = timer_y, ms = timer_ms;
	ENABLE_IRQ

	int i = 0;
	while (i < y){
		block_scheduler();
		int temp_y = main_terminal.row;
		int temp_x = main_terminal.column;
		main_terminal.row = y;
   		main_terminal.column = 70;
		printint_at_date(timer_tick2++);
		main_terminal.row = temp_y;
		main_terminal.column = temp_x;
		unlock_scheduler();
		sleep(ms);
		i++;
	}
}
mutex_t m;
int32_t var = 0;
void test_mut(){
	for (int i = 0;  i < 1000000; i++){
		for (int j = 0;  j < 1000000; j++){
			mutex_lock(&m);
			var++;
			var++;
			var++;
			var++;
			var++;
			var++;
			var++;
			var++;
			var++;
			var++;
			var--;
			var--;
			var--;
			var--;
			var--;
			var--;
			var--;
			var--;
			var--;
			var--;
			mutex_unlock(&m);
		}
	}
}


int command(char *str) {
	flush();
	keyboard.enter = process;
	if (*str == 0) return 1;
	else if (*str == 'r' && *(str + 1) == 'u' && *(str + 2) == 'n' && *(str + 3) == 0){
		_run();
		return 1;
	}
	else if (*str == 'm' && *(str + 1) == 'u' && *(str + 2) == 't' && *(str + 3) == 0){
		DISABLE_IRQ
		add_thread((uint32_t)test_mut, "t1");
		add_thread((uint32_t)test_mut, "t2");
		ENABLE_IRQ
		sleep(5000);
		print("var: %d\n", var);
		return 1;
	}
	else if (*str == 'e' && *(str + 1) == 'c' && *(str + 2) == 'h' && *(str + 3) == 'o' && *(str + 4) == 0){
		if (*(str + 4) == 0) return 1;
		_echo(str + 5);
		return 1;
	}
	else if (*str == 'h' && *(str + 1) == 'e' && *(str + 2) == 'l' && *(str + 3) == 'p' && *(str + 4) == 0){
		_help();
		return 1;
	}
	else if (*str == 'k' && *(str + 1) == 'i' && *(str + 2) == 'l' && *(str + 3) == 'l' && *(str + 4) == 0){
		int s;
		print("Enter thread id: ");
		if (!scan("%d", &s) || s < 1){
			print("Invalid value!\n");
			return 1;
		}
		_kill(s);
		return 1;
	}
	else if (*str == 't' && *(str + 1) == 'e' && *(str + 2) == 'r' && *(str + 3) == 'm' && *(str + 4) == 0){
		int y = 0;
		int ms = 0;
		print("Set y: ");
		if (!scan("%d", &y) || y < 0 || y >= 25){
			print("Invalid value!\n");
			return 1;
		} 
		print("Set interval in ms: ");
		if (!scan("%d", &ms) || ms < 0){
			print("Invalid value!\n");
			return 1;
		} 
		DISABLE_IRQ
		timer_y = y;
		timer_ms = ms;
		add_thread((uint32_t)_term, "term");	
		ENABLE_IRQ
		return 1;
	}
	else if (*str == 'c' && *(str + 1) == 'l' && *(str + 2) == 'e' && *(str + 3) == 'a' && *(str + 4) == 'r' && *(str + 5) == 0){
		_clear();
		return 1;
	}
	else if (*str == 't' && *(str + 1) == 'i' && *(str + 2) == 'm' && *(str + 3) == 'e' && *(str + 4) == 'r' && *(str + 5) == 0){
		int y = 0;
		int ms = 0;
		print("Set y: ");
		if (!scan("%d", &y) || y < 1 || y >= 25){
			print("Invalid value!\n");
			return 1;
		} 
		print("Set interval in ms: ");
		if (!scan("%d", &ms) || ms < 0){
			print("Invalid value!\n");
			return 1;
		} 
		DISABLE_IRQ
		timer_y = y;
		timer_ms = ms;
		add_thread((uint32_t)_timer, "timer");	
		ENABLE_IRQ
		return 1;
	}

	else if (*str == 's' && *(str + 1) == 'e' && *(str + 2) == 't' && *(str + 3) == 't' && *(str + 4) == 'i' && *(str + 5) == 'm' && *(str + 6) == 'e' && *(str + 7) == 0){
		_settime();
		return 1;
	}
	else if (*str == 't' && *(str + 1) == 'h' && *(str + 2) == 'r'&& *(str + 3) == 'e' && *(str + 4) == 'a' && *(str + 5) == 'd' && *(str + 6) == 's' && *(str + 7) == 0){
		display_threads();
		return 1;
	}
	return 0;
}