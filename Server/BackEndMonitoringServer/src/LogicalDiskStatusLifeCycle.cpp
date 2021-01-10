#include "stdafx.h"
#include "LogicalDiskStatusLifeCycle.h"


void LogicalDiskStatusLifeCycle::ThreadLifeCycle( )
{
	container_in_lifecircle_ = 
		ContainerOfLogicalDisk::FactoryContainerOfLogicalDisk(
		specification_);
	while (true)
	{
		for (const auto& disk : 
			*(container_in_lifecircle_->GetAllLogicalDisk()))
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
