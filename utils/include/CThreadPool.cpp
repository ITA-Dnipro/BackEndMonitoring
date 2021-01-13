#include "stdafx.h"

#include "CThreadPool.h"

CThreadPool::CThreadPool(std::size_t num_threads, CEvent& stop_event)
	: m_stop_event(stop_event)
{
	for (size_t i = 0; i < num_threads; ++i) 
	{
		m_threads.emplace_back([=]
		{
			ThreadWork();
		});
	}
}

CThreadPool::~CThreadPool()
{
	m_stop_event.Set();
	m_event.Set();
	for (auto& thread : m_threads) 
	{
		thread.join();
	}
}

void CThreadPool::ThreadWork()
{
	while (true) 
	{
		Task task;

		if (m_stop_event.WaitFor(std::chrono::nanoseconds(1))) 
		{
			break;
		}

		{
			auto [queue, mtx] = m_tasks_queue.GetAccess();

			while (queue.empty()) 
			{
				mtx.unlock();
				m_event.Wait();
				mtx.lock();
			}

			task = std::move(queue.front());
			queue.pop();
		}

		task();
	}
}

