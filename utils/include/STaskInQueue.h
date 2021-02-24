#pragma once

#include <future>

template <typename TaskType>
struct STaskInQueue 
{
	std::future<TaskType> future;
	size_t position;
};