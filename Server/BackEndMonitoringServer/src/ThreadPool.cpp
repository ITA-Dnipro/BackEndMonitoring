#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t num_threads) : free_threads(num_threads)
{
    for (auto i = 0u; i < num_threads; ++i)
    {
        threads.emplace_back([=]
        {
            ThreadWork();
        });
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock{event_mutex};
        is_need_to_stop = true;
    }

    event.notify_all();

    for (auto &thread : threads){
        thread.join();
    }
}

void ThreadPool::ThreadWork(){
    while (true)
    {
        Task task;
        {
            std::unique_lock<std::mutex> lock(event_mutex);

            event.wait(lock, [=]
            {
                return is_need_to_stop || !tasks_queue.empty();
            });

            if (is_need_to_stop && tasks_queue.empty())
            {
                break;
            }

            task = std::move(tasks_queue.front());
            tasks_queue.pop();
        }

        event_mutex.lock();
        free_threads--;
        event_mutex.unlock();

        task();
        
        event_mutex.lock();
        free_threads++;
        event_mutex.unlock();
    }
}

bool ThreadPool::HasFreeThread()
{
    event_mutex.lock();
    bool result = free_threads > 0;
    event_mutex.unlock();
    return result;
}