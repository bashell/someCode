#ifndef _MUTEX_LOCK_H_
#define _MUTEX_LOCK_H_

#include <pthread.h>
#include <stdexcept>

class MutexLock {
 public:
  MutexLock() {
    if(pthread_mutex_init(&lock_, NULL))
      throw std::runtime_error("initialize lock failed!");
  }
  ~MutexLock() {
    if(pthread_mutex_destroy(&lock_))
      throw std::runtime_error("destroy lock failed!");
  }
  void lock() {
    if(pthread_mutex_lock(&lock_)) 
      throw std::runtime_error("lock failed!");
  }
  void unlock() {
    if(pthread_mutex_unlock(&lock_))
      throw std::runtime_error("unlock failed!");
  }
  pthread_mutex_t *getMutexLockPtr() {  // 这里提供指针是为了cond的wait操作, 并且不能为const
    return &lock_;
  }

 private:
  pthread_mutex_t lock_;
};

#endif  // _MUTEX_LOCK_H_
