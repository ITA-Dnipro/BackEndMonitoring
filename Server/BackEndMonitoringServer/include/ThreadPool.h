#pragma once

#include <future>
#include <queue>
#include <condition_variable>
#include <functional>

#include "Event.h"
#include "ThreadSafeVariable.h"
#include "TaskInQueue.h"

class ThreadPool 
{
public:
	using Task = std::function<void()>;

	ThreadPool() = delete;
	ThreadPool(std::size_t numThreads, Event& stop_event);
	ThreadPool(const ThreadPool&) = delete;
	ThreadPool(ThreadPool&&) = delete;
	~ThreadPool() noexcept;

	ThreadPool& operator= (const ThreadPool&) = delete;
	ThreadPool& operator= (const ThreadPool&&) = delete;

	template<typename TaskType>
	[[nodiscard]] auto Enqueue(TaskType task) -> TaskInQueue<decltype(task())>
	{
		auto p_task_wrapper = std::make_shared<std::packaged_task<
							  decltype(task())()>>(std::move(task));

		TaskInQueue<decltype(task())> future_and_pos;
		{
			auto [queue, mtx] = tasks_queue.GetAccess();
			queue.emplace([=]
						  {
							  (*p_task_wrapper)();
						  });
			future_and_pos.position = queue.size();
		}
		event.NotifyOne();

		future_and_pos.future = p_task_wrapper->get_future();
		return future_and_pos;
	}

private:
	void ThreadWork();

private:
	std::vector<std::thread> threads;
	Event event;
	ThreadSafeVariable<std::queue<Task>> tasks_queue;

	Event& stop_event;
};
