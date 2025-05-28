#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for (size_t i = 0; i < numThreads; i++) {
        workers.emplace_back([this] { // Create a thread worker
            while (true) {
                std::unique_lock<std::mutex> lock(queueMutex);
                condition.wait(lock, [this] { return stop || !tasks.empty(); });

                if (stop && tasks.empty()) { return; }

                auto task = std::move(tasks.front());
                tasks.pop_front();
                lock.unlock();
                task(); // Perform the task
            }
        });
    }
}

ThreadPool::~ThreadPool() {
    std::unique_lock<std::mutex> lock(queueMutex);
    stop = true;
    lock.unlock(); 

    condition.notify_all(); // Notify all worker threads to wake up
    for (std::thread &worker : workers) { // Destroy worker threads
        worker.join();
    }
        
}
