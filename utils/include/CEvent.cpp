#include "stdafx.h"

#include "CLogger/include/Log.h"

#include "CEvent.h"

void CEvent::Wait()
{
	CLOG_DEBUG_START_FUNCTION();
	std::unique_lock<std::mutex> lock(m_event_lock);
	CLOG_TRACE_VAR_CREATION(lock);
	m_event_condition.wait(lock, [this]()
	{
		return this->m_is_flash || this->m_is_all_set;
	});

	if (!m_is_all_set)
	{
		m_is_flash = false;
	}
	CLOG_DEBUG_END_FUNCTION();
}

void CEvent::NotifyOne()
{
	CLOG_DEBUG_START_FUNCTION();
	std::lock_guard<std::mutex> lock(m_event_lock);
	CLOG_TRACE_VAR_CREATION(lock);
	m_is_flash = true;
	m_event_condition.notify_one();
	CLOG_DEBUG_END_FUNCTION();
}

void CEvent::Set()
{
	CLOG_DEBUG_START_FUNCTION();
	std::lock_guard<std::mutex> lock(m_event_lock);
	CLOG_TRACE_VAR_CREATION(lock);
	m_is_all_set = true;
	m_event_condition.notify_all();
	CLOG_DEBUG_END_FUNCTION();
}

void CEvent::Reset()
{
	CLOG_DEBUG_START_FUNCTION();
	std::lock_guard<std::mutex> lock(m_event_lock);
	CLOG_TRACE_VAR_CREATION(lock);
	m_is_flash = m_is_all_set = false;
	CLOG_DEBUG_END_FUNCTION();
}