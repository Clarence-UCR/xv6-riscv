#include "kernel/types.h"
#include "user/user.h"
#include "kernel/riscv.h"

int thread_create(void *(*start_routine)(void*), void *arg) {
  void *stack = malloc(PGSIZE);
  if (stack == 0) {
    return -1;
  }

  printf("this is the stack %d\n", stack);
  int pid = clone(stack);
  printf("thread created %d\n", pid);
  if (pid == 0) {
    start_routine(arg);
    exit(0);
  } else if (pid > 0) {
    return 0;
  } else {
    free(stack);
    return -1;
  }
}

void lock_init(struct lock_t* lock) {
  lock->locked = 0;
}

void lock_acquire(struct lock_t* lock) {
  while (__sync_lock_test_and_set(&lock->locked, 1) != 0) {

  }
}

void lock_release(struct lock_t* lock) {
  __sync_lock_release(&lock->locked, 0);
}







