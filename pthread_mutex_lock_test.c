#include "pthread_mutex_lock.h"

DECLARE_GLOBALS;

static pthread_mutex_t global_pthread_mutex_lock;

static void* inc_thread(void *id)
{
    long i, tid = (long)id;

    if (tid == 0)
        gettimeofday(&start_time, NULL);

    for (i = 0; i < NR_LOOP; i++)
    {
        pthread_mutex_lock_lock(&global_pthread_mutex_lock);
        global_counter = global_counter + 1;
        pthread_mutex_lock_unlock(&global_pthread_mutex_lock);
    }

    return NULL;
}

void pthread_mutex_lock_test_main()
{
    pthread_mutex_lock_init(&global_pthread_mutex_lock);

    DO_TEST();

    pthread_mutex_lock_destroy(&global_pthread_mutex_lock);
}
