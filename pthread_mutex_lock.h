#ifndef __PTHREAD_MUTEX_LOCK__
#define __PTHREAD_MUTEX_LOCK__

#include "share.h"
#include <pthread.h>

static void pthread_mutex_lock_init (pthread_mutex_t *mutex)
{
    pthread_mutex_init(mutex, NULL);
}

static void pthread_mutex_lock_destroy (pthread_mutex_t *mutex)
{
    pthread_mutex_destroy(mutex);
}

static void pthread_mutex_lock_lock (pthread_mutex_t *mutex)
{
    pthread_mutex_lock(mutex);
}

static void pthread_mutex_lock_unlock (pthread_mutex_t *mutex)
{
    pthread_mutex_unlock(mutex);
}

#endif
