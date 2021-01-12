#include "stdafx.h"

#include "CLogicalDiskStatusLifeCycle.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CJSONFormatSaver.h"
#include "CEvent.h"

void CLogicalDiskStatusLifeCycle::ThreadLifeCycle( )
{
	m_p_container_in_lifecircle = 
		ÑContainerOfLogicalDisk::FactoryContainerOfLogicalDisk(
		*m_p_specification);
	CJSONFormatSaver json_saver(
		*m_p_container_in_lifecircle->GetPathToSaveFile());
	CJSONFormatterLogicalDisk json_formatter;

	if (nullptr == m_p_container_in_lifecircle)
	{
		std::cout << "Problem with creating container!";
		return;
	}
	while (!m_stop_event.WaitFor(m_p_specification->GetPauseDuration()))
	{
		size_t disk_number = 0;

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
				return;
			}
			disk_number++;
			if (!json_saver.TrySaveToFile(json_formatter))
			{
				//exception handler
				return;

			}
			// check status "Ask info for client-side"
		}
	}
	std::cout << "Fuck!";
}
