
#include <mutex>
#include <condition_variable>

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

// Non-Qt version of QSemaphore
class Semaphore
{
public:
    Semaphore(int count_ = 0) :
        count(count_) {}

    inline void acquire(int n = 1)
    {
        std::unique_lock<std::mutex> lock(mtx);
        while (n > count) cv.wait(lock);
        count -= n;
    }

    inline bool tryAcquire(int n = 1)
    {
        std::unique_lock<std::mutex> lock(mtx);
        if (n > count) {
            return false;
        } else {
            count -= n;
            return true;
        }
    }

    inline void release(int n = 1)
    {
        std::unique_lock<std::mutex> lock(mtx);
        count += n;
        cv.notify_all();
    }

    inline int available() const
    {
        std::unique_lock<std::mutex> lock(mtx);
        return count;
    }

private:
    mutable std::mutex mtx; // 'mutable' allows mutex to be used in const member functions (i.e., available()).
    std::condition_variable cv;
    int count;
};

#endif // SEMAPHORE_H
