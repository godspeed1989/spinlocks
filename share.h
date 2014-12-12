#ifndef __SHARE_H__
#define __SHARE_H__

#include <time.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

#ifndef BOOL
#define BOOL  int
#endif
#ifndef true
#define true  1
#endif
#ifndef false
#define false 0
#endif
#ifndef barrier
#define barrier asm volatile("": : :"memory")
#endif
#ifndef cpu_relax
#define cpu_relax asm volatile("pause\n": : :"memory")
#endif

#define NR_LOOP    999999
#define NR_THREAD       4

static void calc_time (struct timeval *start, struct timeval *end)
{
    if (end->tv_usec < start->tv_usec) {
        end->tv_sec -= 1;
        end->tv_usec += 1000000;
    }
    assert(end->tv_sec >= start->tv_sec);
    assert(end->tv_usec >= start->tv_usec);
    struct timeval interval = {
        end->tv_sec - start->tv_sec,
        end->tv_usec - start->tv_usec
    };
    printf("%ld.%06ld\n", (long)interval.tv_sec, (long)interval.tv_usec);
}

#define DECLARE_GLOBALS                     \
    static unsigned long global_counter;    \
    static struct timeval start_time;       \
    static struct timeval end_time;

#define DO_TEST()                                       \
{                                                       \
    long i;                                             \
    pthread_t threads[NR_THREAD];                       \
    for (i = 0; i < NR_THREAD; i++)                     \
        if (pthread_create(&threads[i], NULL,           \
            inc_thread, (void*)i) != 0)                 \
            perror("thread creating failed");           \
    for (i = 0; i < NR_THREAD; i++)                     \
        pthread_join(threads[i], NULL);                 \
    printf("%s(): ", __FUNCTION__);                     \
    if (global_counter == NR_LOOP * NR_THREAD)          \
        printf("PASS ");                                \
    else                                                \
        printf("FAILED %lu != %lu ", global_counter,    \
        (unsigned long)(NR_LOOP*NR_THREAD));            \
    gettimeofday(&end_time, NULL);                      \
    calc_time(&start_time, &end_time);                  \
}

#endif
