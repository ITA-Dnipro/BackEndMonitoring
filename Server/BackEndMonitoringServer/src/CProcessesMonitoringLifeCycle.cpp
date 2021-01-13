#include "stdafx.h"

#include <thread>

#include "CJSONFormatSaver.h"
#include "CProcessesMonitoringLifeCycle.h"

CProcessesMonitoringLifeCycle::CProcessesMonitoringLifeCycle(
	unsigned max_size,
	std::chrono::duration<int> pause_duration,
	std::string path_to_file,
	EMemoryCountType count_type,
	CEvent& stop_event,
	CThreadSafeVariable<CJSONFormatterProcess>& json_formatter) :
		m_container(max_size, pause_duration, path_to_file, count_type),
		m_json_formatter(json_formatter),
		CHardwareInfoLifeCycle(stop_event)
{ }

void CProcessesMonitoringLifeCycle::ThreadLifeCycle( )
{
	CJSONFormatSaver json_saver(*m_container.GetPathToSaveFile( ));
	while (!m_stop_event.WaitFor(m_container.GetPauseDuration( )))
	{
		{
			auto [json_formatter, mtx] = m_json_formatter.GetAccess( );

			if (!json_formatter.TryAllEraseData( ))
			{
				continue;
			}
			auto processes = m_container.GetAllProcesses( );

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
		m_container.TryToUpdateCurrentStatus( );
	}
}
