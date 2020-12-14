#include <stdint.h>

#include "../include/threads.h"


void threads_install(){
    threads_control.cur_task_index = 0;
	threads_control.active_threads = 0;
	threads_control.running_task_id = 0;
	threads_control.mutex = LOCKED;
}

// void add_task(void (*fun)(void), uint32_t stack_address, uint32_t *pagedir){
//     threads_control.thread[threads_control.cur_task_index].state = SLEEPING;
// 	threads_control.thread[threads_control.cur_task_index].page_dir = pagedir;
// 	threads_control.thread[threads_control.cur_task_index].fun_name = fun;
// 	threads_control.thread[threads_control.cur_task_index].p_id = threads_control.cur_task_index++;
//     threads_control.active_threads++;
// }
void add_task(void (*fun)(void), uint32_t stack_address){
    threads_control.thread[threads_control.cur_task_index].state = SLEEPING;
	threads_control.thread[threads_control.cur_task_index].fun_name = fun;
	threads_control.thread[threads_control.cur_task_index].p_id = threads_control.cur_task_index++;
    threads_control.active_threads++;
}
void scheluder(){
	// DISABLE_IRQ
	// save old process regs
	threads_control.thread[threads_control.running_task_id++].fun_name();
	if (threads_control.running_task_id >= threads_control.active_threads) threads_control.running_task_id = 0;

	// ENABLE_IRQ
	// run other task by running task id
}
void mutex_lock(){
	threads_control.mutex = LOCKED;
}
void mutex_relase(){
	threads_control.mutex = RELASED;
}
