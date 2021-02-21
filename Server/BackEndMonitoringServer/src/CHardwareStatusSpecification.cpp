#include "stdafx.h"

#include "EMemoryConvertType.h"
#include "CHardwareStatusSpecification.h"
#include "CLogger/include/Log.h"

CHardwareStatusSpecification::CHardwareStatusSpecification(
	std::chrono::duration<int> pause_duration,
	EMemoryConvertType count_type) :
	m_pause_duration(pause_duration), m_count_type(count_type)
{ };

CHardwareStatusSpecification::CHardwareStatusSpecification(
	const CHardwareStatusSpecification& orig) :
	m_pause_duration(orig.m_pause_duration),
	m_count_type(orig.m_count_type)
{ };

std::chrono::duration<int> 
CHardwareStatusSpecification::GetPauseDuration() const
{ return m_pause_duration; }

EMemoryConvertType CHardwareStatusSpecification::GetCountType() const
{ return m_count_type; }

bool CHardwareStatusSpecification::CloneObject(
	const CHardwareStatusSpecification& orig)
{
	CLOG_DEBUG_START_FUNCTION();
	m_count_type = orig.m_count_type;
	m_pause_duration = orig.m_pause_duration;
	CLOG_DEBUG_END_FUNCTION();
	return true;
}

