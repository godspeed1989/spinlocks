#include "spin_lock_xchg.h"

DECLARE_GLOBALS;

static spin_lock_xchg_t global_spin_lock;

static void* inc_thread(void *id)
{
    long i, tid = (long)id;

    if (tid == 0)
        gettimeofday(&start_time, NULL);

    for (i = 0; i < NR_LOOP; i++)
    {
        spin_lock_xchg(&global_spin_lock);
        global_counter = global_counter + 1;
        spin_unlock_xchg(&global_spin_lock);
    }

    return NULL;
}

void spin_lock_xchg_test_main()
{
    spin_lock_xchg_init(&global_spin_lock);

    DO_TEST();

    spin_lock_xchg_destroy(&global_spin_lock);
}
