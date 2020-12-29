#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>
#include "isr.h"

#define THREAD_STACK_SIZE 4096

enum mutex_state {
    RELASED,
    LOCKED
};

enum threads_state_t
{
    THREAD_WAITING_FOR_START,
    THREAD_READY,
    THREAD_RUNNING,
    THREAD_RIP
};

struct threads_t
{
    uint32_t esp;
    uint32_t stack;
    uint32_t task;
    uint32_t thread_id;
    uint32_t next_thread_id;
    uint8_t name[16];
    volatile enum threads_state_t state;
};
void add_thread(uint32_t function_pointer, const char *name);
void create_thread(struct threads_t *new_thread, uint32_t *stack, uint32_t task_addr, const char *name);
void task_switch(struct threads_t *current, struct threads_t *next);
extern void switch_stacks_and_jump(uint32_t current_thread, uint32_t next_thread);
extern void switch_stacks(uint32_t current_thread, uint32_t next_thread);
void display_threads();


struct threads_control_t {
    struct threads_t thread[16];
    uint32_t stacks[16][THREAD_STACK_SIZE];
    uint8_t active_threads;
    uint8_t thread_index;
    enum mutex_state mutex;
} threads_control;

void threads_install();
void scheluder();
void mutex_lock();
void mutex_relase();




#endif