#ifndef __ARRAY_BASED_LOCK__
#define __ARRAY_BASED_LOCK__

#include "share.h"

/*
 * array based spin lock implementation
 */
typedef struct _array_based_lock_t
{
    unsigned int size;      // 抢占的线程个数
    volatile unsigned int tail;
    BOOL *flag;
}array_based_lock_t;

static void array_based_lock_init (array_based_lock_t *lock, unsigned int size)
{
    lock->size = size;
    lock->tail = 0;
    lock->flag = (BOOL*)malloc(sizeof(BOOL)*size);
}

static void array_based_lock_destroy (array_based_lock_t *lock)
{
    if (lock->flag)
        free(lock->flag);
}

static void array_based_lock (array_based_lock_t *lock, unsigned int *slot)
{
    unsigned int newslot = __sync_fetch_and_add(&lock->tail, 1) % lock->size;
    *slot = newslot;

    while (!lock->flag[newslot])
    {
        cpu_relax;
    }
}

static void array_based_unlock(array_based_lock_t *lock, int slot)
{
    lock->flag[slot] = false;
    lock->flag[(slot + 1) % lock->size] = true;
}

#endif
