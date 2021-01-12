#pragma once

#include <mutex>

template <typename T>
class ThreadSafeVariable 
{
public:
	ThreadSafeVariable() = default;
	explicit ThreadSafeVariable(T&& value)
		: value(value)
	{ }
	ThreadSafeVariable(ThreadSafeVariable&) = delete;
	ThreadSafeVariable(ThreadSafeVariable&&) = delete;
	~ThreadSafeVariable() noexcept = default;

	struct Access 
	{
		T& ref_to_value;
		std::unique_lock<std::mutex> guard;
	};

	Access GetAccess()
	{
		return {value, std::unique_lock(m)};
	}

private:
	T value;
	std::mutex m;
};

