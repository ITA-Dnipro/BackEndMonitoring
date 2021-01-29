#include "stdafx.h"

#include "CThreadPool.h"

CThreadPool::CThreadPool(std::size_t num_threads, CEvent& stop_event)
	: m_stop_event(stop_event)
{
	CLOG_TRACE_START_FUNCTION( );
	m_threads.emplace_back([=]
						   {
							   CheckThread( );
						   });
	CLOG_TRACE("Started check thread");
	for (size_t i = 0; i < num_threads; ++i)
	{
		m_threads.emplace_back([=]
							   {
								   ThreadWork( );
							   });
		CLOG_TRACE("Pushed thread " + std::to_string(i) + " in pool");
	}
	CLOG_TRACE_END_FUNCTION( );
}

CThreadPool::~CThreadPool( )
{
	CLOG_TRACE_START_FUNCTION( );
	m_stop_event.Set( );
	CLOG_TRACE("Setted stop event");
	m_event.Set( );
	CLOG_TRACE("Setted internal event");
	for (auto& thread : m_threads)
	{
		thread.join( );
		CLOG_TRACE("Joined thread");
	}
	CLOG_TRACE_END_FUNCTION( );
}

void CThreadPool::ThreadWork( )
{
	CLOG_TRACE_START_FUNCTION( );
	while (true)
	{
		Task task;

		CLOG_TRACE_VAR_CREATION(task);
		{
			auto [queue, mtx] = m_tasks_queue.GetAccess( );

			while (queue.empty( ))
			{
				CLOG_TRACE("Entered the queue.empty() condition block");
				mtx.unlock( );
				CLOG_TRACE("Unlocked queue mutex and waiting for internal event");
				m_event.Wait( );
				CLOG_TRACE("Catched internal event");
				
				if (m_stop_event.WaitFor(std::chrono::nanoseconds(1)))
				{
					CLOG_TRACE("Unlocked queue mutex and setted internal event in queue.empty( ) stop event condition block");
					m_event.Set( );
					CLOG_TRACE("Returned from queue.empty( ) stop event condition block");
					return;
				}
				CLOG_TRACE("Passed the queue.empty( ) stop event condition block");

				mtx.lock( );
				CLOG_TRACE("Locked queue mutex");
			}
			CLOG_TRACE("Passed the queue.empty() condition block");

			if (m_stop_event.WaitFor(std::chrono::nanoseconds(1)))
			{
				CLOG_TRACE("Entered the stop event block");
				mtx.unlock( );
				CLOG_TRACE("Unlocked queue mutex and setted internal event in stop event condition block");
				m_event.Set( );
				CLOG_TRACE("Breaked ThreadWork wgile from stop event condition block");
				break;
			}
			CLOG_TRACE("Passed the stop event condition block");

			task = std::move(queue.front( ));
			CLOG_TRACE("Moved task from the queue");
			queue.pop( );
			CLOG_TRACE("Poped task from the queue");
		}

		CLOG_TRACE("Started executing task");
		task( );
		CLOG_TRACE("Ended executing task");
	}
	CLOG_TRACE_END_FUNCTION( );
}

void CThreadPool::CheckThread( )
{
	CLOG_TRACE_START_FUNCTION( );
	CLOG_TRACE("Waiting for stop event");
	m_stop_event.Wait( );
	CLOG_TRACE("Catched stop event");
	m_event.Set( );
	CLOG_TRACE("Setted internal event");
	CLOG_TRACE_END_FUNCTION( );
}