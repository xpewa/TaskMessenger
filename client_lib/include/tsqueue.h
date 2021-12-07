#ifndef TASKMESSENGER_TSQUEUE_H
#define TASKMESSENGER_TSQUEUE_H

#include <queue>
#include <mutex>

template <class T>
class TSQueue {
public:
  TSQueue() = default;
  ~TSQueue() { mutex.lock(); }

  void push(T &element) {
    mutex.lock();
    queue.push(element);
    mutex.unlock();
  }
  T front() {
    mutex.lock();
    T res = queue.front();
    mutex.unlock();
    return res;
  }
  void pop() {
    mutex.lock();
    queue.pop();
    mutex.unlock();
  }
  bool empty() {
    mutex.lock();
    bool res = queue.empty();
    mutex.unlock();
    return res;
  }

private:
  std::queue<T> queue;
  std::mutex mutex;
};

#endif // TASKMESSENGER_TSQUEUE_H
