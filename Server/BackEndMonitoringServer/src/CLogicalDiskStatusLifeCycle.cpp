#include "stdafx.h"

#include "CLogicalDiskStatusLifeCycle.h"

void CLogicalDiskStatusLifeCycle::ThreadLifeCycle( )
{
	m_container_in_lifecircle = 
		ÑContainerOfLogicalDisk::FactoryContainerOfLogicalDisk(
		*m_specification);

	if (nullptr == m_container_in_lifecircle)
	{
		std::cout << "Problem with creating container!";
		return;
	}
	while (true)
	{
		for (const auto& disk : 
			*(m_container_in_lifecircle->GetAllLogicalDisk()))
		{
			if (!disk->TryUpdateCurrentStatus())
			{
				std::cout << "Enable to update!" << std::endl;
				break;
			}
			std::cout << *disk->GetDiskName() << std::endl;
			std::cout << disk->GetCapacityOfDisk() << std::endl;
			std::cout << disk->GetFreeSpaceOfDisk() << std::endl;

			// check status "Ask info for client-side"

			// add data to JSON-formattor

		}
			// pause
	}
}
