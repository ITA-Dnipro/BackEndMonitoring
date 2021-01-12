#include "stdafx.h"

#include "CEvent.h"

void CEvent::Wait()
{
	std::unique_lock<std::mutex> lock(m_event_lock);
	m_event_condition.wait(lock, [this]()
	{
		return this->m_is_flash || this->m_is_all_set;
	});

	if (!m_is_all_set)
	{
		m_is_flash = false;
	}
}

void CEvent::NotifyOne()
{
	std::lock_guard<std::mutex> lock(m_event_lock);
	m_is_flash = true;
	m_event_condition.notify_one();
}

void CEvent::Set()
{
	std::lock_guard<std::mutex> lock(m_event_lock);
	m_is_all_set = true;
	m_event_condition.notify_all();
}

void CEvent::Reset()
{
	std::lock_guard<std::mutex> lock(m_event_lock);
	m_is_flash = m_is_all_set = false;
}