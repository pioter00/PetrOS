#include <stdint.h>

#include "../include/threads.h"
#include "../include/std.h"
#include "../include/isr.h"
#include "../include/macros.h"

#define cur_proc threads_control.thread[threads_control.cur_task_index] 

void threads_install(){
	threads_control.active_threads = 0;
	threads_control.thread_index = 0;
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
void add_thread(uint32_t function_pointer, const char *name){
    create_thread(&threads_control.thread[threads_control.active_threads], threads_control.stacks[threads_control.active_threads], function_pointer, name);
}
void create_thread(struct threads_t *new_thread, uint32_t *stack, uint32_t task_addr, const char *name){
    new_thread->state = THREAD_WAITING_FOR_START;
    new_thread->stack = (uint32_t)stack;
    new_thread->esp = new_thread->stack + THREAD_STACK_SIZE;
    new_thread->task = task_addr;
    new_thread->thread_id = threads_control.active_threads;
    mem_cpy(new_thread->name, name, strlen(name) + 1);
    threads_control.thread[threads_control.active_threads].next_thread_id = 0; 
    if (threads_control.active_threads > 0){
        threads_control.thread[threads_control.active_threads - 1].next_thread_id = threads_control.active_threads;
    }
    threads_control.active_threads++;
}
void display_threads(){
    for(unsigned i = 0; i < threads_control.active_threads; i++){
        print("%d. %s id: %d\n", i + 1, threads_control.thread[i].name,threads_control.thread[i].thread_id);
    }
}
void task_switch(struct threads_t *current, struct threads_t *next){
    DISABLE_IRQ
	if(next->state == THREAD_WAITING_FOR_START)
    {
        next->state = THREAD_READY;
        switch_stacks_and_jump((uint32_t)current, (uint32_t)next);
    }
    else if(next->state == THREAD_READY){
        switch_stacks((uint32_t)current, (uint32_t)next);
    }
    ENABLE_IRQ
}
