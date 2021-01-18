#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>

#define THREAD_STACK_SIZE 4096
#define THREAD_NUMBER 16


enum threads_state_t
{
    THREAD_WAITING_FOR_START,
    THREAD_SLEEPING,
    THREAD_RUNNING,
    THREAD_TERMINATED
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
void create_thread(struct threads_t *new_thread, uint32_t *stack, uint32_t task_addr, const char *name, uint32_t id);
void task_switch(struct threads_t *current, struct threads_t *next);
extern void switch_stacks_and_jump(uint32_t current_thread, uint32_t next_thread);
extern void switch_stacks(uint32_t current_thread, uint32_t next_thread);
void display_threads();
void display_active_threads();
static void push_thread32(struct threads_t *t, uint32_t val);
void terminate();

struct threads_control_t {
    struct threads_t thread[THREAD_NUMBER];
    uint32_t stacks[THREAD_NUMBER][THREAD_STACK_SIZE];
    uint8_t active_threads;
    uint8_t thread_index;
} threads_control;

void threads_install();
void scheduler();
typedef uint8_t mutex_t;
mutex_t m;
void mutex_lock(mutex_t *m);
void mutex_unlock(mutex_t *m);

void block_scheduler();
void unlock_scheduler();

#endif