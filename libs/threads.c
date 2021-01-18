#include <stdint.h>

#include "../include/threads.h"
#include "../include/terminal.h"
#include "../include/std.h"
#include "../include/isr.h"
#include "../include/macros.h"
#include "../include/timer.h"


void threads_install(){
	threads_control.active_threads = 0;
	threads_control.thread_index = 0;
    for (int i = 0; i < THREAD_NUMBER; i++){
        threads_control.thread[i].state = THREAD_TERMINATED;
        if (i == THREAD_NUMBER - 1) threads_control.thread[i].next_thread_id = 0;
        else threads_control.thread[i].next_thread_id = i + 1;
    }
}

void mutex_lock(mutex_t *m){
    while (!__sync_bool_compare_and_swap(m, 0, 1)){
        scheduler();
    }
}
void mutex_unlock(mutex_t *m){
    *m = 0;
    scheduler();
}

void block_scheduler(){
    DISABLE_IRQ
}   
void unlock_scheduler(){
    ENABLE_IRQ
    scheduler();
}

int32_t find_index(){
    for (int i = 0; i < THREAD_NUMBER; i++){
        if (threads_control.thread[i].state == THREAD_TERMINATED) return i;
    }
    return -1;
}
void add_thread(uint32_t function_pointer, const char *name){
    uint32_t temp = find_index();
    if (temp == -1) print("Threads list full!\n");
    else create_thread(&threads_control.thread[temp], threads_control.stacks[temp], function_pointer, name, temp);
}
void create_thread(struct threads_t *new_thread, uint32_t *stack, uint32_t task_addr, const char *name, uint32_t id){
    new_thread->state = THREAD_WAITING_FOR_START;
    new_thread->stack = (uint32_t)stack;
    new_thread->esp = new_thread->stack + THREAD_STACK_SIZE;
    new_thread->task = task_addr;
    push_thread32(new_thread, (uint32_t)terminate);
    new_thread->thread_id = id;
    mem_set(new_thread->name, 0, 16);
    mem_cpy(new_thread->name, name, strlen(name) + 1);
    if (id == threads_control.active_threads) threads_control.thread[id].next_thread_id = 0;
    else threads_control.thread[id].next_thread_id = id + 1;
    if (threads_control.active_threads > 0){
        threads_control.thread[id - 1].next_thread_id = id;
    }
    threads_control.active_threads++;
}

void display_threads(){
    unsigned j = 1;
    for(unsigned i = 0; ; i = threads_control.thread[i].next_thread_id, j++){
        print("%d.  NAME: %s id: %d STATUS: ", j, threads_control.thread[i].name,threads_control.thread[i].thread_id);
        if (threads_control.thread[i].state == THREAD_WAITING_FOR_START) print("waiting");
        else if (threads_control.thread[i].state == THREAD_RUNNING) print("running");
        else if (threads_control.thread[i].state == THREAD_SLEEPING) print("sleeping");
        else if (threads_control.thread[i].state == THREAD_TERMINATED) print("terminated");
        print("\n");
        if (threads_control.thread[i].next_thread_id == 0) break;
    }
}
void task_switch(struct threads_t *current, struct threads_t *next){
    DISABLE_IRQ
	if(next->state == THREAD_WAITING_FOR_START)
    {
        next->state = THREAD_SLEEPING;
        switch_stacks_and_jump((uint32_t)current, (uint32_t)next);
    }
    else if (next->state == THREAD_SLEEPING || THREAD_RUNNING){
        current->state = THREAD_SLEEPING;
        next->state = THREAD_RUNNING;
        switch_stacks((uint32_t)current, (uint32_t)next);
    }
    ENABLE_IRQ
}
void scheduler(){
    if (threads_control.active_threads > 0) {
        DISABLE_IRQ
        unsigned temp = threads_control.thread_index;
        unsigned temp1 = threads_control.thread[threads_control.thread_index].next_thread_id;
        if (threads_control.thread[temp1].state == THREAD_TERMINATED){
            threads_control.thread[temp].next_thread_id = threads_control.thread[temp1].next_thread_id;
            temp1 = threads_control.thread[temp1].next_thread_id;
        }
        threads_control.thread_index = temp1;
        task_switch(&threads_control.thread[temp], &threads_control.thread[temp1]);
    }
}

void terminate(){
    threads_control.thread[threads_control.thread_index].state = THREAD_TERMINATED;
    while (1) __asm__ ("nop");
}
static void push_thread8(struct threads_t *t, uint8_t val)
{
    t->esp--;
    uint8_t *addr = (uint8_t*)t->esp;
    *addr = val;
}
static void push_thread32(struct threads_t *t, uint32_t val)
{
    uint8_t b1 = (val & 0x000000FF) >> 0;
    uint8_t b2 = (val & 0x0000FF00) >> 8;
    uint8_t b3 = (val & 0x00FF0000) >> 16;
    uint8_t b4 = (val & 0xFF000000) >> 24;

    push_thread8(t, b4);
    push_thread8(t, b3);
    push_thread8(t, b2);
    push_thread8(t, b1);
}