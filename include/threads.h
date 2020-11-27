#ifndef THREADS_H
#define THREADS_H

#include <stdint.h>
struct thread_t
{
    void *func;
    struct thread_t *next;
    uint8_t state;
};
struct threads_control_t
{
    struct thread_t thread[64];
    uint8_t active_threads;
} threads_control;

#endif