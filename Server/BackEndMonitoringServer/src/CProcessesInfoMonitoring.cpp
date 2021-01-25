#include "stdafx.h"

#include "CContainerOfProcesses.h"
#include "CJSONFormatterProcess.h"
#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CProcessInfo.h"
#include "CProcessesInfoMonitoring.h"
#include "CEvent.h"

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
{ }

bool CProcessesInfoMonitoring::Initialize()
{
	m_is_initialized = m_container.Initialize() 
					   && m_container.TryToUpdateCurrentStatus();
	return m_is_initialized;
}

bool CProcessesInfoMonitoring::StartMonitoringInfo( )
{
	if(!m_is_initialized)
	{ return false;}


	CJSONFormatSaver json_saver(
		*m_container.GetSpecification()->GetPathToSaveFile( ));
	while (!m_stop_event.WaitFor(
		m_container.GetSpecification()->GetPauseDuration( )))
	{
		{
			auto [json_formatter, mtx] = m_json_formatter.GetAccess( );

			if (!json_formatter.TryEraseAllData( ))
			{
				continue;
			}
			std::list<CProcessInfo> processes;
			if (m_container.GetAllProcesses(processes))
			{
				for (auto& process : processes)
				{
					if (!json_formatter.TryAddProcessData(process))
					{
						continue;
					}
				}
				if (!json_saver.TrySaveToFile(json_formatter))
				{
					//exception handler
					continue;
				}
			}
		}
		m_container.TryToUpdateCurrentStatus( );
	}
	return true;
}
