#include "stdafx.h"

#include "�HardwareStatusSpecification.h"

std::chrono::duration<int> 
�HardwareStatusSpecification::GetPauseDuration() const
{ return m_pause_duration; }

EMemoryCountType �HardwareStatusSpecification::GetCountType() const
{ return m_count_type; }

std::string* �HardwareStatusSpecification::GetPathToSaveFile()
{ return &m_path_to_file; }
