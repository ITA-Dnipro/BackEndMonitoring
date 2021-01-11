#include "stdafx.h"

#include "ThreadPool.h"

ThreadPool::ThreadPool(std::size_t num_threads, Event& stop_event)
	: stop_event(stop_event)
{
	for (size_t i = 0; i < num_threads; ++i) {
		threads.emplace_back([=]
		{
			ThreadWork();
		});
	}
}

ThreadPool::~ThreadPool()
{
	stop_event.Set();
	event.Set();
	for (auto& thread : threads) {
		thread.join();
	}
}

void ThreadPool::ThreadWork()
{
	while (true) {
		Task task;

		if (stop_event.WaitFor(std::chrono::nanoseconds(1))) {
			break;
		}

		{
			auto [queue, mtx] = tasks_queue.GetAccess();

			while (queue.empty()) {
				mtx.unlock();
				event.Wait();
				mtx.lock();
			}

			task = std::move(queue.front());
			queue.pop();
		}

		task();
	}
}

