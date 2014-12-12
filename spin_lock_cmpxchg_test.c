#include "spin_lock_cmpxchg.h"

DECLARE_GLOBALS;

static spin_lock_cmpxchg_t global_spin_lock;

static void* inc_thread(void *id)
{
    long i, tid = (long)id;

    if (tid == 0)
        gettimeofday(&start_time, NULL);

    for (i = 0; i < NR_LOOP; i++)
    {
        spin_lock_cmpxchg(&global_spin_lock);
        global_counter = global_counter + 1;
        spin_unlock_cmpxchg(&global_spin_lock);
    }

    return NULL;
}

void spin_lock_cmpxchg_test_main()
{
    spin_lock_cmpxchg_init(&global_spin_lock);

    DO_TEST();

    spin_lock_cmpxchg_destroy(&global_spin_lock);
}
