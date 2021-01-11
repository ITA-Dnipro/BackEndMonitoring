#pragma once

#include <condition_variable>

class Event 
{
public:
	Event() = default;
	Event(const Event&) = delete;
	Event(Event&&) = delete;
	~Event() noexcept = default;

	Event& operator = (const Event&) = delete;
	Event& operator = (const Event&&) = delete;

	void Wait();

	template <typename Rep, typename Period>
	bool WaitFor(const std::chrono::duration<Rep, Period>& duration)
	{
		std::unique_lock<std::mutex> lock(event_lock);
		bool result = event_condition.wait_for(lock, duration, 
											   [this]()
											   {
												   return this->is_flash ||
													   this->is_all_set;
											   });
		if (result && !is_all_set) {
			is_flash = false;
		}
		return result;
	}

	template <typename Clock, typename Duration>
	bool WaitUntil(const std::chrono::time_point<Clock, Duration>& point)
	{
		std::unique_lock<std::mutex> lock(event_lock);
		bool result = event_condition.wait_until(lock, point, 
												[this]()
												{
													return this->is_flash ||
														this->is_all_set;
												});
		if (result && !is_all_set) {
			is_flash = false;
		}
		return result;
	}

	void NotifyOne();

	void Set();
	void Reset();

private:
	bool is_flash = false;
	bool is_all_set = false;

	std::mutex event_lock;
	std::condition_variable event_condition;
};
