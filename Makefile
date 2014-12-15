CC=gcc
CFLAGS=-g -Wall -Wno-unused-function
OBJS=test.o array_based_lock_test.o     \
            pthread_mutex_lock_test.o   \
            spin_lock_xchg_test.o       \
            spin_lock_cmpxchg_test.o

RM=rm -rf

# in cmd of windows
ifeq ($(SHELL),sh.exe)
    RM := del /f/q
endif

all: test

test: $(OBJS)
	$(CC) -o $@ $^ -lpthread

clean:
	$(RM) *.o test test.exe
