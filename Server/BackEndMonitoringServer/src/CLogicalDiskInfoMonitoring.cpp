#include "stdafx.h"

#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CContainerOfLogicalDisk.h"
#include "CLogicalDiskInfo.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CLogicalDiskInfoMonitoring.h"
#include "CEvent.h"
#include "CLogger/include/Log.h"
#include "Utils.h"

#include "CLogger/include/Log.h"

CLogicalDiskInfoMonitoring::CLogicalDiskInfoMonitoring(
	CEvent& stop_event,
	CHardwareStatusSpecification* specification,
	CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter) :
	IHardwareInfoMonitoring(stop_event),
	m_p_specification(std::move(specification)),
	m_p_container(nullptr),
	m_json_formatter(json_formatter)
{ };

CLogicalDiskInfoMonitoring::CLogicalDiskInfoMonitoring(
	CHardwareStatusSpecification* specification,
	CContainerOfLogicalDisk* container_in_lifecircle,
	CEvent& stop_event,
	CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter) :
	m_p_specification(std::move(specification)),
	m_p_container(container_in_lifecircle),
	IHardwareInfoMonitoring(stop_event),
	m_json_formatter(json_formatter)
{ };

CLogicalDiskInfoMonitoring::~CLogicalDiskInfoMonitoring()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr != m_p_specification)
	{
		delete m_p_specification;
	}
	if (nullptr != m_p_container)
	{
		delete m_p_container;
	}
	CLOG_DEBUG_END_FUNCTION();
}

bool CLogicalDiskInfoMonitoring::StartMonitoringInfo()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == m_p_container)
	{
		m_p_container = new CContainerOfLogicalDisk(*m_p_specification);
	}
	if (!m_p_container->InitializeContainerOfLogicalDisk())
	{
		// error
		return false;
	}
	CJSONFormatSaver json_saver(
		*m_p_container->GetSpecification()->GetPathToSaveFile());
	CLOG_TRACE_VAR_CREATION(json_saver);
	if (nullptr == m_p_container)
	{
		std::cout << "Problem with creating container!";
		return false;
	}
	if (!Utils::TryCreateDirectory(
		*m_p_container->GetSpecification()->GetPathToSaveFile()))
	{
		return false;
	}
	m_p_container->GetSpecification()->AddBranchToPath("/");
	std::string common_path = *m_p_container->GetSpecification()->GetPathToSaveFile();

	while (!m_stop_event.WaitFor(m_p_specification->GetPauseDuration()))
	{
		auto [json_formatter, mtx] = m_json_formatter.GetAccess();
		CLOG_TRACE_VAR_CREATION(json_formatter);
		if (!json_formatter.TryEraseAllData())
		{
			continue;
		}
		std::string current_day;
		std::string current_time;
		Utils::TryGetCurrentDay(current_day);
		Utils::TryGetCurrentTime(current_time);
		if (m_p_container->GetSpecification()->GetPathToSaveFile()->substr(
			common_path.length(),
			m_p_container->GetSpecification()->GetPathToSaveFile()->find_last_of('/')) 
			!= current_day)
		{
			if (!Utils::TryCreateDirectory(common_path + current_day))
			{
				//log
				return false;
			}

			m_p_container->GetSpecification()->SetNewPath(common_path + current_day);
		}
		if (Utils::IsHourPassed(m_p_container->GetSpecification()->GetPathToSaveFile()->substr(
			m_p_container->GetSpecification()->GetPathToSaveFile()->find_last_of("/"), 8)))
		{
			m_p_container->GetSpecification()->SetNewPath(common_path + current_day + current_time);
		}
		if (!m_p_container->TryUpdateInfoLogicalDiskToJSON(json_formatter))
		{
			//exception handler
			continue;
		}

		if (!json_saver.TrySaveToFile(json_formatter))
		{
			CLOG_DEBUG("ERROR! FiseSave doesn't work!");
			//exception handler
			continue;
		}
	}
	CLOG_DEBUG_END_FUNCTION();	
	return true;
}
