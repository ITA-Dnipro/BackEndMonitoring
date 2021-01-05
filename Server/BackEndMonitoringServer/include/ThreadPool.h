#pragma once

#include <future>
#include <vector>
#include <queue>
#include <condition_variable>
#include <functional>

class ThreadPool
{
public:
    using Task = std::function<void()>;

    explicit ThreadPool(std::size_t numThreads);
    ~ThreadPool();

    template<typename T>
    auto Enqueue(T task) -> std::future<decltype(task())>
    {
        auto p_task_wrapper =
            std::make_shared<std::packaged_task<decltype(task())()>>(
                    std::move(task));
        {
            std::unique_lock<std::mutex> lock{event_mutex};
            tasks_queue.emplace([=]
            {
                (*p_task_wrapper)();
            });
        }

        event.notify_one();
        return p_task_wrapper->get_future();
    }

    bool HasFreeThread();
private:
    void ThreadWork();

private:
    std::vector<std::thread> threads;

    std::queue<Task> tasks_queue;

    std::condition_variable event;
    std::mutex event_mutex;
    bool is_need_to_stop = false;

    size_t free_threads;
};
