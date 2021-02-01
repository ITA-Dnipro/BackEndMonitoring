#include "Server/BackEndMonitoringServer/include/stdafx.h"

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
	std::string path_to_file,
	EMemoryConvertType count_type,
	CEvent& stop_event,
	CThreadSafeVariable<CJSONFormatterProcess>& json_formatter) :
		m_container(pause_duration, path_to_file, count_type),
		m_json_formatter(json_formatter),
		IHardwareInfoMonitoring(stop_event),
		m_is_initialized(false)
{
	CLOG_TRACE_START_FUNCTION( );
	CLOG_TRACE_END_FUNCTION( );
}

bool CProcessesInfoMonitoring::Initialize()
{
	CLOG_DEBUG_START_FUNCTION( );
	m_is_initialized = m_container.Initialize( ) && 
		m_container.TryToUpdateCurrentStatus();
	if (m_is_initialized)
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
	if(!m_is_initialized)
	{
		CLOG_PROD("ERROR!!! CProcessesInfoMonitoring function was called on uninitialized object");
		return false;
	}


	CJSONFormatSaver json_saver(
		*m_container.GetSpecification()->GetPathToSaveFile( ));
	CLOG_TRACE_VAR_CREATION(json_saver);

	while (!m_stop_event.WaitFor(
		m_container.GetSpecification()->GetPauseDuration( )))
	{
		{
			auto [json_formatter, mtx] = m_json_formatter.GetAccess( );
			CLOG_DEBUG("CProcessesInfoMonitoring obtained the json data mutex");
			if (!json_formatter.TryEraseAllData( ))
			{
				CLOG_PROD("WARNING!!! CProcessesInfoMonitoring can't delete data from json.");
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
				for (auto& process : processes)
				{
					if (!json_formatter.TryAddProcessData(process))
					{
						CLOG_PROD("WARNING!!! CProcessesInfoMonitoring can't add data about process to json.");
						continue;
					}
				}
				if (!json_saver.TrySaveToFile(json_formatter))
				{
					CLOG_PROD("ERROR!!! CProcessesInfoMonitoring can't save json data to file.");
					//exception handler
					continue;
				}
			}
		}
		if (!m_container.TryToUpdateCurrentStatus( ))
		{
			CLOG_PROD("ERROR!!! CProcessesInfoMonitoring can't update processes container.");
		}
	}
	CLOG_DEBUG_END_FUNCTION( );
	return true;
}
