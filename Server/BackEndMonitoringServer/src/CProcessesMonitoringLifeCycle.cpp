#include "stdafx.h"

#include "CContainerOfProcesses.h"
#include "CJSONFormatterProcess.h"
#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CProcess.h"
#include "CProcessesMonitoringLifeCycle.h"
#include "CEvent.h"

CProcessesMonitoringLifeCycle::CProcessesMonitoringLifeCycle(
	unsigned max_size,
	std::chrono::duration<int> pause_duration,
	std::string path_to_file,
	EMemoryCountType count_type,
	CEvent& stop_event,
	CThreadSafeVariable<CJSONFormatterProcess>& json_formatter) :
		m_container(max_size, pause_duration, path_to_file, count_type),
		m_json_formatter(json_formatter),
		CHardwareInfoLifeCycle(stop_event),
		m_is_initialized(false)
{ }

bool CProcessesMonitoringLifeCycle::Initialize()
{
	bool success;
	if (success = m_container.Initialize())
	{
		m_is_initialized = true;
	}
	return success;
}

bool CProcessesMonitoringLifeCycle::ThreadLifeCycle( )
{
	if(!m_is_initialized)
	{
		return false;
	}

	CJSONFormatSaver json_saver(*m_container.GetPathToSaveFile( ));
	while (!m_stop_event.WaitFor(m_container.GetPauseDuration( )))
	{
		{
			auto [json_formatter, mtx] = m_json_formatter.GetAccess( );

			if (!json_formatter.TryEraseAllData( ))
			{
				continue;
			}
			std::vector<CProcess> processes;
			if (m_container.GetAllProcesses(processes))
			{
				for (auto& process : processes)
				{
					if (!json_formatter.TryAddProcessData(process))
					{
						continue;
					}
					if (!json_saver.TrySaveToFile(json_formatter))
					{
						//exception handler
						continue;
					}
				}
			}
		}
		m_container.TryToUpdateCurrentStatus( );
	}
	return true;
}
