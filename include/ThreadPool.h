#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <vector>
#include <vector>
#include <deque>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <atomic>
class ThreadPool {
public:
    // Constructor
    explicit ThreadPool(size_t numThreads = std::thread::hardware_concurrency());

    // Destructor
    ~ThreadPool();

    // Getter
    int getNumWorkers() { return workers.size(); } 

    // Submit a task to the thread pool 
    template <class F, class... Args>
    auto enqueue(F&& f, Args&&... args) -> std::future<typename std::invoke_result_t<F, Args...>>;

private:
    std::vector<std::thread> workers; // Worker threads
    std::deque<std::function<void()>> tasks; // Task queue

    std::mutex queueMutex; // Synchronization
    std::condition_variable condition;
    std::atomic<bool> stop;
};

template <class F, class... Args>
auto ThreadPool::enqueue(F&& task, Args&&... args)
    -> std::future<typename std::invoke_result_t<F, Args...>> {
    if (stop) { throw std::runtime_error("enqueue on stopped ThreadPool"); }
    using return_type = typename std::invoke_result_t<F, Args...>;

    auto taskPtr = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(task), std::forward<Args>(args)...)  
    );

    std::future<return_type> res = taskPtr->get_future(); // Return the future to get() later

    std::unique_lock<std::mutex> lock(queueMutex);
    tasks.emplace_back([taskPtr] { (*taskPtr)(); });
    lock.unlock();
    condition.notify_one(); // Notify any worker thread to take up the task
    return std::move(res); 
}

#endif