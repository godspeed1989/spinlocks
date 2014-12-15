#ifndef __SPIN_LOCK_XCHG__
#define __SPIN_LOCK_XCHG__

#include "share.h"

typedef volatile char spin_lock_xchg_t;

static void spin_lock_xchg_init (spin_lock_xchg_t *lock)
{
    *lock = 0;
}

static void spin_lock_xchg_destroy (spin_lock_xchg_t *lock)
{
}

static char __xchg8 (spin_lock_xchg_t *lock, char x)
{
    __asm__ __volatile__("xchgb %0,%1\r\n"
                :"=r" (x)     // output
                :"m" (*(volatile char *)lock),
                 "0" (x)      // input
                :"memory");

    return x;
}

static void spin_lock_xchg (spin_lock_xchg_t *lock)
{
    while (1)
    {
        if (!__xchg8(lock, 1))
            return;
        while (*lock) cpu_relax;
    }
}

static void spin_unlock_xchg (spin_lock_xchg_t *lock)
{
    barrier;
    *lock = 0;
}

#endif
