#include "stdafx.h"

#include "Event.h"

void Event::Wait()
{
	std::unique_lock<std::mutex> lock(event_lock);
	event_condition.wait(lock, [this]()
						{
							return this->is_flash || this->is_all_set;
						});

	if (!is_all_set) {
		is_flash = false;
	}
}

void Event::NotifyOne()
{
	std::lock_guard<std::mutex> lock(event_lock);
	is_flash = true;
	event_condition.notify_one();
}

void Event::Set()
{
	std::lock_guard<std::mutex> lock(event_lock);
	is_all_set = true;
	event_condition.notify_all();
}

void Event::Reset()
{
	std::lock_guard<std::mutex> lock(event_lock);
	is_flash = is_all_set = false;
}