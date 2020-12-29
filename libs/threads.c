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

void scheluder(){

}
void mutex_lock(){
	threads_control.mutex = LOCKED;
}
void mutex_relase(){
	threads_control.mutex = RELASED;
}

void create_thread(struct threads_t *new_thread, uint32_t *stack, uint32_t task_addr){
	
    new_thread->state = THREAD_WAITING_FOR_START;
    new_thread->stack = (uint32_t)stack;
    new_thread->esp = new_thread->stack + THREAD_STACK_SIZE;
    new_thread->task = task_addr;
    new_thread->priority = 20;
}
void task_schedule(struct threads_t *current, struct threads_t *next){
	if(next->state == THREAD_WAITING_FOR_START)
    {
        next->state = THREAD_READY;
        switch_stacks_and_jump((uint32_t)current, (uint32_t)next);
    }
    else if(next->state == THREAD_READY){
        switch_stacks((uint32_t)current, (uint32_t)next);
    }
}
