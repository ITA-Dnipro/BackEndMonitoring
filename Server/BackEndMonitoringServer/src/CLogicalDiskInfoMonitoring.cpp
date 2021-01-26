#include "stdafx.h"

#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CContainerOfLogicalDisk.h"
#include "CLogicalDiskInfo.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CLogicalDiskInfoMonitoring.h"
#include "CEvent.h"

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
	if (nullptr != m_p_specification)
	{
		delete m_p_specification;
	}
	if (nullptr != m_p_container)
	{
		delete m_p_container;
	}
}

bool CLogicalDiskInfoMonitoring::StartMonitoringInfo()
{
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

	if (nullptr == m_p_container)
	{
		std::cout << "Problem with creating container!";
		return false;
	}
	while (!m_stop_event.WaitFor(m_p_specification->GetPauseDuration()))
	{
		auto [json_formatter, mtx] = m_json_formatter.GetAccess();
		
		if (!json_formatter.TryEraseAllData())
		{
			continue;
		}
		
		m_p_container->TryUpdateInfoLogicalDiskToJSON(json_formatter);

		if (!json_saver.TrySaveToFile(json_formatter))
		{
			//exception handler
			continue;

		}
	}
	return true;
}
