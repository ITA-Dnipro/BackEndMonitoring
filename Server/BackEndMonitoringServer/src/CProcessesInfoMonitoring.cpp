#include "stdafx.h"

#include "CContainerOfProcesses.h"
#include "CJSONFormatterProcess.h"
#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CProcessInfo.h"
#include "CProcessesInfoMonitoring.h"
#include "CEvent.h"
#include "CLogger/include/Log.h"

CProcessesInfoMonitoring::CProcessesInfoMonitoring(
	std::chrono::duration<int> pause_duration,
	EMemoryConvertType count_type, CEvent& stop_event,
	std::shared_ptr<CProcessesInfoJSONDatabase> database,
	std::shared_ptr<CResourcesInfoJSONDatabase> resources_database) :
	m_container(pause_duration, count_type),
	m_p_database(database),
	m_p_resources_database(resources_database),
	IHardwareInfoMonitoring(stop_event),
	m_is_initialized(false)
{
	CLOG_TRACE_START_FUNCTION( );
	CLOG_TRACE_END_FUNCTION( );
}

bool CProcessesInfoMonitoring::Initialize( )
{
	CLOG_DEBUG_START_FUNCTION( );
	if (m_is_initialized = m_container.Initialize( ))
	{
		CLOG_DEBUG("CProcessesInfoMonitoring was initialized");
	}
	else
	{
		CLOG_DEBUG("CProcessesInfoMonitoring wasn't initialized");
	}
	CLOG_DEBUG_END_FUNCTION( );
	return m_is_initialized;
}

bool CProcessesInfoMonitoring::StartMonitoringInfo( )
{
	CLOG_DEBUG_START_FUNCTION( );
	if (!m_is_initialized)
	{
		CLOG_ERROR("CProcessesInfoMonitoring function was called on uninitialized object");
		return false;
	}

	while (!m_stop_event.WaitFor(
		m_container.GetSpecification( )->GetPauseDuration( )))
	{
		if (!m_container.TryToUpdateCurrentStatus( ))
		{
			CLOG_ERROR("CProcessesInfoMonitoring can't update processes container.");
		}

		{
			if (!m_p_database->ClearCommitedData( ))
			{
				CLOG_WARNING("CProcessesInfoMonitoring can't delete data from json.");
				continue;
			}
			else
			{
				CLOG_TRACE("CProcessesInfoMonitoring erased data from json");
			}
			std::list<CProcessInfo> processes;
			CLOG_TRACE_VAR_CREATION(processes);
			if (m_container.GetAllProcesses(processes))
			{
				long double cpu = 0;
				long double ram = 0;
				long double pagefile = 0;
				for (auto& process : processes)
				{
					double temp_cpu;
					if(process.GetCpuUsage(temp_cpu))
					{ cpu += temp_cpu;}
					else
					{ CLOG_WARNING("Can't get info about process CPU usage");}

					long double temp_memory;
					if(process.GetRamUsage(temp_memory))
					{ ram += temp_memory;}
					else
					{ CLOG_WARNING("Can't get info about process RAM usage");}

					if(process.GetPagefileUsage(temp_memory))
					{ pagefile += temp_memory;}
					else
					{ CLOG_WARNING("Can't get info about process pagefile usage");}

					if (!m_p_database->CommitDataAdd(process))
					{
						CLOG_WARNING("CProcessesInfoMonitoring can't add data about process to json.");
					}
				}
				m_p_resources_database->InsertData(cpu, ram, pagefile);

				if (!m_p_database->InsertCommitedData( ))
				{
					CLOG_ERROR("CProcessesInfoMonitoring can't save json data to file.");
				}
			}
		}
	}
	CLOG_DEBUG_END_FUNCTION( );
	return true;
}
