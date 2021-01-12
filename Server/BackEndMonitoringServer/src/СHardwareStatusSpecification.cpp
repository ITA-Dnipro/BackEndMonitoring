#include "stdafx.h"

#include "ÑHardwareStatusSpecification.h"

std::chrono::duration<int> 
ÑHardwareStatusSpecification::GetPauseDuration() const
{ return m_pause_duration; }

EMemoryCountType ÑHardwareStatusSpecification::GetCountType() const
{ return m_count_type; }

std::string* ÑHardwareStatusSpecification::GetPathToSaveFile()
{ return &m_path_to_file; }
