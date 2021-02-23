#include "stdafx.h"

#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CContainerOfLogicalDisk.h"
#include "CLogicalDiskInfo.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CLogicalDiskInfoMonitoring.h"
#include "CEvent.h"
#include "CLogger/include/Log.h"

#include "CLogger/include/Log.h"

CLogicalDiskInfoMonitoring::CLogicalDiskInfoMonitoring(
	CEvent& stop_event,
	CHardwareStatusSpecification* specification,
	std::shared_ptr<CDrivesInfoJSONDatabase> p_database) :
	IHardwareInfoMonitoring(stop_event),
	m_p_specification(std::move(specification)),
	m_p_container(nullptr),
	m_p_database(p_database)
{ };

CLogicalDiskInfoMonitoring::CLogicalDiskInfoMonitoring(
	CHardwareStatusSpecification* specification,
	CContainerOfLogicalDisk* container_in_lifecircle,
	CEvent& stop_event,
	std::shared_ptr<CDrivesInfoJSONDatabase> p_database) :
	m_p_specification(std::move(specification)),
	m_p_container(container_in_lifecircle),
	IHardwareInfoMonitoring(stop_event),
	m_p_database(p_database)
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
		return false;
	}

	if (nullptr == m_p_container)
	{
		CLOG_WARNING("Problem with creating container!");
		return false;
	}
	while (!m_stop_event.WaitFor(m_p_specification->GetPauseDuration()))
	{
		if (!m_p_database->ClearCommitedData())
		{
			continue;
		}
		
		const std::vector<CLogicalDiskInfo*>* p_logical_disks =
			m_p_container->GetAllLogicalDisk( );

		for (const auto& disk : *p_logical_disks)
		{
			if (!disk->TryUpdateCurrentStatus( ))
			{
				// exception
				CLOG_ERROR( "Unable to update logical disks info!" );
				continue;
			}
			if (!m_p_database->CommitDataAdd(*disk))
			{
				//exception handler
				continue;
			}
		}

		if (!m_p_database->InsertCommitedData( ))
		{
			CLOG_ERROR("FiseSave doesn't work!");
			continue;
		}
	}
	CLOG_DEBUG_END_FUNCTION();	
	return true;
}
