#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>
#include "isr.h"


#define THREAD_STACK_SIZE 4096

enum process_state{
	RUNNING,
	SLEEPING
};

enum mutex_state {
    RELASED,
    LOCKED
};

struct thread_t
{
    struct regs *registrers;
	void (*fun_name)(void);
    enum process_state state;
	uint8_t p_id;
};
struct threads_control_t
{
    struct thread_t thread[16];
    uint8_t cur_task_index;
    uint8_t active_threads;
	uint8_t running_task_id;
    enum mutex_state mutex;
} threads_control;

void threads_install();
void add_task(void (*fun_name)(void), uint32_t stack_address);
void scheluder();
void mutex_lock();
void mutex_relase();

extern void switch_task(struct regs* current, struct regs* next);


#endif