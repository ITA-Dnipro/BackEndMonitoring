#include "stdafx.h"

#include "CThreadSafeVariable.h"
#include "CJSONFormatSaver.h"
#include "CContainerOfLogicalDisk.h"
#include "CLogicalDiskStatus.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CLogicalDiskStatusLifeCycle.h"

CLogicalDiskStatusLifeCycle::~CLogicalDiskStatusLifeCycle()
{
	delete m_p_specification;
	delete m_p_container_in_lifecircle;
}

bool CLogicalDiskStatusLifeCycle::ThreadLifeCycle( )
{
	m_p_container_in_lifecircle = 
		CContainerOfLogicalDisk::FactoryContainerOfLogicalDisk(
		*m_p_specification);
	CJSONFormatSaver json_saver(
		*m_p_container_in_lifecircle->GetPathToSaveFile());

	if (nullptr == m_p_container_in_lifecircle)
	{
		std::cout << "Problem with creating container!";
		return false;
	}
	while (!m_stop_event.WaitFor(m_p_specification->GetPauseDuration()))
	{
		auto [json_formatter, mtx] = m_json_formatter.GetAccess( );
		
		if (!json_formatter.TryEraseAllData( ))
		{
			continue;
		}

		unsigned short disk_number = 0;

		for (const auto& disk :
			*(m_p_container_in_lifecircle->GetAllLogicalDisk()))
		{

			if (!disk->TryUpdateCurrentStatus())
			{
				std::cout << "Enable to update!" << std::endl;
				break;
			}
			if (!json_formatter.TryAddLogicalDiskData(*disk, disk_number))
			{
				//exception handler
				continue;
			}
			disk_number++;
			if (!json_saver.TrySaveToFile(json_formatter))
			{
				//exception handler
				continue;

			}
		}
	}
	return true;
}
