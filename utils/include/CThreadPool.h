#pragma once

#include <queue>
#include <condition_variable>
#include <functional>

#include "CEvent.h"
#include "CThreadSafeVariable.h"
#include "STaskInQueue.h"

class CThreadPool
{
public:
	using Task = std::function<void()>;

	CThreadPool() = delete;
	CThreadPool(std::size_t numThreads, CEvent& stop_event);
	CThreadPool(const CThreadPool&) = delete;
	CThreadPool(CThreadPool&&) noexcept = delete;
	~CThreadPool() noexcept;

	CThreadPool& operator= (const CThreadPool&) = delete;
	CThreadPool& operator= (CThreadPool&&) noexcept = delete;

	template<typename TaskType>
	[[nodiscard]] auto Enqueue(TaskType task) -> STaskInQueue<decltype(task())>
	{
		auto p_task_wrapper = std::make_shared<std::packaged_task<
			decltype(task())()>>(std::move(task));

		STaskInQueue<decltype(task())> future_and_pos;
		{
			auto [queue, mtx] = m_tasks_queue.GetAccess();
			queue.emplace([=]
			{
				(*p_task_wrapper)();
			});
			future_and_pos.position = queue.size();
		}
		m_event.NotifyOne();

		future_and_pos.future = p_task_wrapper->get_future();
		return future_and_pos;
	}

private:
	void ThreadWork();

private:
	std::vector<std::thread> m_threads;
	CEvent m_event;
	CThreadSafeVariable<std::queue<Task>> m_tasks_queue;

	CEvent& m_stop_event;

};
