#include "array_based_lock.h"

DECLARE_GLOBALS;

static array_based_lock_t global_array_based_lock;
static unsigned int slot[NR_THREAD];

static void* inc_thread(void *id)
{
    long i, tid = (long)id;

    if (tid == 0)
        gettimeofday(&start_time, NULL);

    for (i = 0; i < NR_LOOP; i++)
    {
        array_based_lock(&global_array_based_lock, &slot[tid]);
        global_counter = global_counter + 1;
        array_based_unlock(&global_array_based_lock, slot[tid]);
    }

    return NULL;
}

void array_based_lock_test_main()
{
    array_based_lock_init(&global_array_based_lock, NR_THREAD);

    DO_TEST();

    array_based_lock_destroy(&global_array_based_lock);
}
