#pragma once

#include <future>
#include <queue>
#include <condition_variable>
#include <functional>

#include "CEvent.h"
#include "CThreadSafeVariable.h"
#include "STaskInQueue.h"
#include "CLogger/include/Log.h"

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
	[[nodiscard]] auto Enqueue(TaskType task) -> STaskInQueue<decltype(task( ))>
	{
		STaskInQueue<decltype(task( ))> future_and_pos;
		CLOG_DEBUG_START_FUNCTION( );
		CLOG_TRACE_VAR_CREATION(future_and_pos);

		auto p_task_wrapper = std::make_shared<std::packaged_task<
			decltype(task( ))()>>(std::move(task));
		CLOG_TRACE_VAR_CREATION(p_task_wrapper);

		STaskInQueue<decltype(task( ))> future_and_pos;
		{
			auto [queue, mtx] = m_tasks_queue.GetAccess( );
			CLOG_DEBUG("Obtained queue mutex");
			queue.emplace([=]
						  {
							  (*p_task_wrapper)();
						  });
			CLOG_DEBUG("Pushed task in queue");

			future_and_pos.position = queue.size( );
			CLOG_TRACE_VAR_CREATION(future_and_pos.position);
		}
		m_event.NotifyOne( );
		CLOG_DEBUG("Notified one thread that task pushed");

		future_and_pos.future = p_task_wrapper->get_future( );
		CLOG_TRACE_VAR_CREATION(future_and_pos.future);

		CLOG_DEBUG_END_FUNCTION( );
		return future_and_pos;
	}

private:
	void ThreadWork();
	void CheckThread( );

private:
	CEvent m_event;
	CThreadSafeVariable<std::queue<Task>> m_tasks_queue;
	std::vector<std::thread> m_threads;
	CEvent& m_stop_event;
};
