#ifndef __SPIN_LOCK_CMPXCHG__
#define __SPIN_LOCK_CMPXCHG__

#include "share.h"

typedef volatile char spin_lock_cmpxchg_t;

static void spin_lock_cmpxchg_init (spin_lock_cmpxchg_t *lock)
{
    *lock = 0;
}

static void spin_lock_cmpxchg_destroy (spin_lock_cmpxchg_t *lock)
{
}

static char __cmpxchg(spin_lock_cmpxchg_t *lock)
{
    char readval = 0;

    asm volatile (
              "lock; cmpxchgb %b2, %0\r\n"
            : "+m" (*lock), "+a" (readval) // output
            : "r" (1) // input
            : "cc"    // modified (condition codes)
            );
    return readval;
}

static void spin_lock_cmpxchg (spin_lock_cmpxchg_t *lock)
{
    while (__cmpxchg(lock))
    {
        cpu_relax;
    }
}

static void spin_unlock_cmpxchg (spin_lock_cmpxchg_t *lock)
{
    barrier;
    *lock = 0;
}

#endif
