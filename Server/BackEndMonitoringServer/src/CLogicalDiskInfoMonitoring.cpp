#include "stdafx.h"

#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CContainerOfLogicalDisk.h"
#include "CLogicalDiskInfo.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CLogicalDiskInfoMonitoring.h"
#include "CEvent.h"
#include "CLogger/include/Log.h"

CLogicalDiskInfoMonitoring::CLogicalDiskInfoMonitoring(
	CEvent& stop_event,
	std::shared_ptr<CHardwareStatusSpecification>& specification,
	CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter) :
	IHardwareInfoMonitoring(stop_event),
	m_p_specification(std::move(specification)),
	m_p_container(nullptr),
	m_json_formatter(json_formatter)
{ };

CLogicalDiskInfoMonitoring::CLogicalDiskInfoMonitoring(
	std::shared_ptr<CHardwareStatusSpecification>& specification,
	std::shared_ptr<CContainerOfLogicalDisk>& container_in_lifecircle,
	CEvent& stop_event,
	CThreadSafeVariable<CJSONFormatterLogicalDisk>& json_formatter) :
	m_p_specification(std::move(specification)),
	m_p_container(std::move(container_in_lifecircle)),
	IHardwareInfoMonitoring(stop_event),
	m_json_formatter(json_formatter)
{ };

CLogicalDiskInfoMonitoring::~CLogicalDiskInfoMonitoring()
{ }

bool CLogicalDiskInfoMonitoring::StartMonitoringInfo()
{
	CLOG_DEBUG_START_FUNCTION();
	if (nullptr == m_p_container)
	{
		m_p_container = std::make_shared< CContainerOfLogicalDisk>(
			CContainerOfLogicalDisk(*m_p_specification));
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
	while (!m_stop_event.WaitFor(m_p_specification->GetPauseDuration()))
	{
		auto [json_formatter, mtx] = m_json_formatter.GetAccess();
		CLOG_TRACE_VAR_CREATION(json_formatter);
		if (!json_formatter.TryEraseAllData())
		{
			continue;
		}
		
		if (!m_p_container->TryUpdateInfoLogicalDiskToJSON(json_formatter))
		{
			//exception handler
			continue;
		}

		if (!json_saver.TrySaveToFile(json_formatter))
		{
			//exception handler
			continue;
		}
	}
	CLOG_DEBUG_END_FUNCTION();	
	return true;
}
