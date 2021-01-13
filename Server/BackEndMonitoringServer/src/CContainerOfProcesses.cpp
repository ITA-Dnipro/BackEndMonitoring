#include "stdafx.h"

#include <windows.h>
#include <psapi.h>
#include <algorithm>

#include "CContainerOfProcesses.h"

CContainerOfProcesses::CContainerOfProcesses(
	unsigned m_max_process_count, std::chrono::duration<int> 
	pause_duration, std::string path_to_file, EMemoryCountType count_type) :
	m_max_process_count(m_max_process_count),
	ÑHardwareStatusSpecification(pause_duration, path_to_file, count_type)
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);
	m_processors_count = sysInfo.dwNumberOfProcessors;

	std::list<DWORD> list_of_PIDs;
	if (GetListOfProcessIds(list_of_PIDs))
	{
		for (auto PID : list_of_PIDs)
		{
			CProcess temp(PID, m_processors_count, m_count_type);
			if (temp.TryToUpdateCurrentStatus())
			{
				m_container.push_back(temp);
			}
		}
	}
}

bool CContainerOfProcesses::TryToUpdateCurrentStatus()
{
	std::list<DWORD> list_of_PIDs;
	bool success = GetListOfProcessIds(list_of_PIDs);

	if (success)
	{
		for (auto PID : list_of_PIDs)
		{
			auto it = std::find_if(m_container.begin(), m_container.end(),
								   [PID](const CProcess& proc)
			{
				return proc.GetPID() == PID;
			});

			if (it == m_container.end())
			{
				m_container.push_back(CProcess(PID, m_processors_count, 
													m_count_type));
			}
			else
			{
				it->TryToUpdateCurrentStatus();
			}
		}

		auto dead_process = std::find_if(m_container.begin(), 
										 m_container.end(), 
										 [](const CProcess& proc)
		{
			return !proc.IsActive();
		});

		while (dead_process != m_container.end())
		{
			m_container.erase(dead_process);
			dead_process = std::find_if(m_container.begin(), m_container.end(),
									    [](const CProcess& proc)
			{
				return !proc.IsActive();
			});
		}
	}
	return success;
}

bool CContainerOfProcesses::GetListOfProcessIds(std::list<DWORD>& list_of_PIDs)
const
{
	DWORD success = NO_ERROR;
	DWORD* p_process_ids = new DWORD[m_max_process_count];
	DWORD cb = m_max_process_count * sizeof(DWORD);
	DWORD bytes_returned = 0;

	if (::EnumProcesses(p_process_ids, cb, &bytes_returned))
	{
		const int size = bytes_returned / sizeof(DWORD);
		for (int index = 0; index < size; index++)
		{
			list_of_PIDs.push_back(p_process_ids[index]);
		}
	}
	else
	{
		success = ::GetLastError();
	}
	delete[] p_process_ids;

	return success == NO_ERROR;
}

std::vector<CProcess> CContainerOfProcesses::GetAllProcesses()
{return m_container;};