#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>
#include "isr.h"

enum process_state{
	RUNNING,
	SLEEPING
};

struct thread_t
{
    //struct regs *stack_frame;
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
} threads_control;

void threads_install();
void add_task(void (*fun_name)(void), uint32_t stack_address);
void scheluder();

#endif