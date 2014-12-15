#include "share.h"
#include "array_based_lock.h"
#include "pthread_mutex_lock.h"
#include "spin_lock_xchg.h"
#include "spin_lock_cmpxchg.h"
#include <unistd.h>

extern void array_based_lock_test_main();
extern void pthread_mutex_lock_test_main();
extern void spin_lock_xchg_test_main();
extern void spin_lock_cmpxchg_test_main();

int main()
{
    printf("Number of Thread(s): %d\n", NR_THREAD);
    printf("Number of Loop(s): %d\n", NR_LOOP);

    array_based_lock_test_main();
    sleep(1);
    pthread_mutex_lock_test_main();
    sleep(1);
    spin_lock_xchg_test_main();
    sleep(1);
    spin_lock_cmpxchg_test_main();

    return 0;
}
