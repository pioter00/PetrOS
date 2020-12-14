#include <stdint.h>

#include "../include/threads.h"
#include "../include/std.h"
#include "../include/isr.h"

#define cur_proc threads_control.thread[threads_control.cur_task_index] 

void threads_install(){
    threads_control.cur_task_index = 0;
	threads_control.active_threads = 0;
	threads_control.running_task_id = 0;
	threads_control.mutex = LOCKED;
}

void add_task(void (*fun)(void), uint32_t stack_address){

	uint32_t* process_kernel_stack = (uint32_t*)stack_address;
	struct regs *cpu_state = cur_proc.registrers;
	cpu_state->ebp = stack_address;
	cpu_state->esp = stack_address + THREAD_STACK_SIZE - 4 * 5;
	cpu_state->edi = 0;
	cpu_state->ebx = 0;
	cpu_state->esi = 0;

    process_kernel_stack[THREAD_STACK_SIZE/4 - 5] = cpu_state->ebp;
    process_kernel_stack[THREAD_STACK_SIZE/4 - 4] = cpu_state->edi;
    process_kernel_stack[THREAD_STACK_SIZE/4 - 3] = cpu_state->esi;
    process_kernel_stack[THREAD_STACK_SIZE/4 - 2] = cpu_state->ebx;
    process_kernel_stack[THREAD_STACK_SIZE/4 - 1] = (uint32_t)fun;

    cur_proc.state = RUNNING;
	cur_proc.fun_name = fun;
	cur_proc.p_id = threads_control.cur_task_index++;
	print("add task id: %d\n", cur_proc.p_id);
    threads_control.active_threads++;
}
void scheluder(){
	// save old process regs
	uint8_t temp = threads_control.running_task_id++;
	if (threads_control.running_task_id >= threads_control.active_threads) threads_control.running_task_id = 0;
	switch_task(threads_control.thread[temp].registrers, threads_control.thread[threads_control.running_task_id].registrers);
	// print("switch to task id: %d\n", threads_control.running_task_id);
	// run other task by running task id
}
void mutex_lock(){
	threads_control.mutex = LOCKED;
}
void mutex_relase(){
	threads_control.mutex = RELASED;
}
