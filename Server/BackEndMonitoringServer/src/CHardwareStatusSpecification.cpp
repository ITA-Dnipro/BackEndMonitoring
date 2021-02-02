#include "stdafx.h"

#include "EMemoryConvertType.h"
#include "CHardwareStatusSpecification.h"

CHardwareStatusSpecification::CHardwareStatusSpecification(
	std::chrono::duration<int>
	pause_duration, const std::string& path_to_file,
	EMemoryConvertType count_type) :
	m_pause_duration(pause_duration), m_path_to_file(path_to_file),
	m_count_type(count_type)
{ };

CHardwareStatusSpecification::CHardwareStatusSpecification(
	const CHardwareStatusSpecification& orig) :
	m_pause_duration(orig.m_pause_duration),
	m_path_to_file(orig.m_path_to_file),
	m_count_type(orig.m_count_type)
{ };

std::chrono::duration<int> 
CHardwareStatusSpecification::GetPauseDuration() const
{ return m_pause_duration; }

EMemoryConvertType CHardwareStatusSpecification::GetCountType() const
{ return m_count_type; }

const std::string* CHardwareStatusSpecification::GetPathToSaveFile() const
{ return &m_path_to_file; }

bool CHardwareStatusSpecification::CloneObject(
	const CHardwareStatusSpecification& orig)
{
	m_count_type = orig.m_count_type;
	m_path_to_file = orig.m_path_to_file;
	m_pause_duration = orig.m_pause_duration;

	return true;
}
