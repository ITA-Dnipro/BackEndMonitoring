#include "stdafx.h"

#include "CProcessInfo.h"
#include "PlatformUtils.h"
#include "CLogger/include/Log.h"

#include "CContainerOfProcesses.h"

CContainerOfProcesses::CContainerOfProcesses(std::chrono::duration<int>
		pause_duration, const std::string& path_to_file, 
		EMemoryConvertType count_type) :
	m_specification(pause_duration, path_to_file, count_type),
	m_is_initialized(false)
{ }

bool CContainerOfProcesses::Initialize()
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	CLOG_TRACE_VAR_CREATION(success);

	std::vector<unsigned> PIDs;
	CLOG_TRACE_VAR_CREATION(PIDs);
	if (success = PlatformUtils::GetExistingProcessIds(PIDs))
	{
		for (auto PID : PIDs)
		{
			CProcessInfo temp(PID, m_specification.GetCountType());
			CLOG_TRACE_VAR_CREATION(temp);
			if (success = temp.Initialize( ))
			{
				CLOG_TRACE_WITH_PARAMS("Process ", PID,	" added to container");
				m_container.push_back(std::move(temp));
			}
			else
			{
				CLOG_TRACE_WITH_PARAMS("WARNING!!! Can't initialize process ",
					PID);
			}
		}
	}
	else
	{
		CLOG_PROD("ERROR!!! Can't get list of existing PID's.");
	}
	m_is_initialized = success;
	CLOG_TRACE_VAR_CREATION(m_is_initialized);
	CLOG_DEBUG_END_FUNCTION( );
	return success;
}

bool CContainerOfProcesses::TryToUpdateCurrentStatus()
{
	bool success = true;
	CLOG_DEBUG_START_FUNCTION( );
	if (!m_is_initialized)
	{ 
		CLOG_ERROR("Call function on uninitialized container of processes");
		return false;
	}

	std::vector<unsigned> PIDs;
	CLOG_TRACE_VAR_CREATION(PIDs);
	
	success = PlatformUtils::GetExistingProcessIds(PIDs);
	if (success)
	{
		CLOG_TRACE("Existing PID's recieved successfully");
		for (auto PID : PIDs)
		{
			auto it = std::find_if(m_container.begin(), m_container.end(),
								   [PID](const CProcessInfo& proc)
			{
				unsigned val;
				return  proc.GetPID(val) ? val == PID : false;
			});

			if (it == m_container.end())
			{
				CProcessInfo temp(PID, m_specification.GetCountType());
				CLOG_TRACE_VAR_CREATION(temp);
				if (temp.Initialize())
				{
					m_container.push_back(std::move(temp));
					CLOG_TRACE_WITH_PARAMS("Process ", PID,
						" was added to container");
				}
				else
				{
					CLOG_TRACE_WITH_PARAMS("Process ", PID, 
						" wasn't initialised");
				}
			}
			else
			{
				if (!it->TryToUpdateCurrentStatus())
				{
					m_container.erase(it);
					CLOG_TRACE_WITH_PARAMS("Process ", PID,
						" was erased from container");
				}
				else
				{
					CLOG_TRACE_WITH_PARAMS("Process ", PID, " was updated");
				}
			}
		}

		EraseDeadProcesses( );
	}
	else
	{
		CLOG_ERROR("Can't get existing PID's");
	}
	CLOG_DEBUG_END_FUNCTION( );
	return success;
}

bool CContainerOfProcesses::GetAllProcesses(std::list<CProcessInfo>& to_list)  
{
	CLOG_DEBUG_START_FUNCTION( );
	if (m_is_initialized)
	{
		to_list = m_container;
		CLOG_TRACE_VAR_CREATION(to_list);
	}
	else
	{
		CLOG_ERROR("Call function on uninitialized container of processes");
	}
	CLOG_DEBUG_END_FUNCTION( );
	return m_is_initialized;
};

const CHardwareStatusSpecification* CContainerOfProcesses::GetSpecification()
const
{ 
	CLOG_TRACE_START_FUNCTION( );
	CLOG_TRACE_END_FUNCTION( );
	return &m_specification;
}

void CContainerOfProcesses::EraseDeadProcesses()
{
	CLOG_TRACE_START_FUNCTION()
	auto dead_process = std::find_if(m_container.begin(),
		m_container.end(),
		[](const CProcessInfo& proc)
		{
			return !proc.IsActive();
		});

	while (dead_process != m_container.end())
	{
		m_container.erase(dead_process);
		CLOG_TRACE("Inactive process was erased from container");
		dead_process = std::find_if(m_container.begin(), m_container.end(),
			[](const CProcessInfo& proc)
			{
				return !proc.IsActive();
			});
	}
	CLOG_TRACE_END_FUNCTION();
}
