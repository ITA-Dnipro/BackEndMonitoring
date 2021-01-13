#pragma once

#include <condition_variable>

class CEvent
{
public:
	CEvent() = default;
	CEvent(const CEvent&) = delete;
	CEvent(CEvent&&) noexcept = delete;
	~CEvent() noexcept = default;

	CEvent& operator = (const CEvent&) = delete;
	CEvent& operator = (CEvent&&) noexcept = delete;

	void Wait();

	template <typename Rep, typename Period>
	bool WaitFor(const std::chrono::duration<Rep, Period>& duration)
	{
		std::unique_lock<std::mutex> lock(m_event_lock);
		bool result = m_event_condition.wait_for(lock, duration, [this]()
		{
			return this->m_is_flash ||
				this->m_is_all_set;
		});

		if (result && !m_is_all_set)
		{
			m_is_flash = false;
		}
		return result;
	}

	template <typename Clock, typename Duration>
	bool WaitUntil(const std::chrono::time_point<Clock, Duration>& point)
	{
		std::unique_lock<std::mutex> lock(m_event_lock);
		bool result = m_event_condition.wait_until(lock, point, [this]()
		{
			return this->m_is_flash ||
				this->m_is_all_set;
		});

		if (result && !m_is_all_set)
		{
			m_is_flash = false;
		}
		return result;
	}

	void NotifyOne();

	void Set();
	void Reset();

private:
	bool m_is_flash = false;
	bool m_is_all_set = false;

	std::mutex m_event_lock;
	std::condition_variable m_event_condition;

};
