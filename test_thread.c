#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

lock_thread* lock;

void first(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  printf(1, "1. this should print %s\n", num ? "first" : "whenever");
  printf(1, "1. sleep for %d units\n", 100);
  sleep(100);
  if (num)
    lock_release(lock);
  exit();
}

void second(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  printf(1, "2. this should print %s\n", num ? "second" : "whenever");
  printf(1, "2. sleep for %d units\n", 100);
  sleep(100);
  if (num)
    lock_release(lock);
  exit();
}

void third(void* arg1, void* arg2) {
  int num = *(int*)arg1;
  if (num) lock_acquire(lock);
  printf(1, "3. this should print %s\n", num ? "third" : "whenever");
  printf(1, "3. sleep for %d units\n", 100);
  sleep(100);
  if (num)
    lock_release(lock);
  exit();
}

int
main(int argc, char *argv[])
{
  lock_init(lock);
  int arg1 = 1;
  int arg2 = 1;

  printf(1, "there are 2 print statements for every thread:\n");
  thread_create(&first, (void *)&arg1, (void *)&arg2);
  thread_create(&second, (void *)&arg1, (void *)&arg2);
  thread_create(&third, (void *)&arg1, (void *)&arg2);
  thread_join();
  thread_join();
  thread_join();
  exit();
}