#pragma once

#include <future>

template <typename TaskType>
struct TaskInQueue 
{
	std::future<TaskType> future;
	size_t position;
};