#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>
class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads = std::thread::hardware_concurrency());
    ~ThreadPool();

    // Submit a task to the thread pool 
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result_t<F, Args...>>;
    int getNumWorkers() { return workers.size(); } 


private:
    // Worker threads
    std::vector<std::thread> workers;

    // Task queue
    std::queue<std::function<void()>> tasks;

    // Synchronization
    std::mutex queueMutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};

template <class F, class... Args>
auto ThreadPool::enqueue(F&& task, Args&&... args)
    -> std::future<typename std::invoke_result_t<F, Args...>> {
    using return_type = typename std::invoke_result_t<F, Args...>;

    auto taskPtr = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(task), std::forward<Args>(args)...)  
    );
    std::future<return_type> res = taskPtr->get_future();

    std::unique_lock<std::mutex> lock(queueMutex);
    tasks.emplace([taskPtr] { (*taskPtr)(); });
    lock.unlock();
    condition.notify_one();
    return res;
}

#endif