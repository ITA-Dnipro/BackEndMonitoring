#include "stdafx.h"

#include "CProcess.h"
#include "CContainerOfProcesses.h"
#include "PlatformUtils.h"

CContainerOfProcesses::CContainerOfProcesses(std::chrono::duration<int> 
	pause_duration, std::string path_to_file, EMemoryCountType count_type) :
	m_processors_count(0),
	CHardwareStatusSpecification(pause_duration, path_to_file, count_type),
	m_is_initialized(false)
{ }

bool CContainerOfProcesses::Initialize()
{
	m_processors_count = std::thread::hardware_concurrency( );
	
	if(m_processors_count == 0)
	{ return false;}

	std::list<unsigned> list_of_PIDs;
	bool success;
	if (success = PlatformUtils::GetListOfProcessIds(list_of_PIDs))
	{
		for (auto PID : list_of_PIDs)
		{
			CProcess temp(PID, m_processors_count, m_count_type);
			success = temp.Initialize();
			if (success = temp.TryToUpdateCurrentStatus())
			{
				m_container.push_back(std::move(temp));
			}
		}
	}
	if (success)
	{
		m_is_initialized = true;
	}
	return success;
}

bool CContainerOfProcesses::TryToUpdateCurrentStatus()
{
	if (!m_is_initialized) {
		return false;
	}

	std::list<unsigned> list_of_PIDs;
	bool success = PlatformUtils::GetListOfProcessIds(list_of_PIDs);

	if (success)
	{
		for (auto PID : list_of_PIDs)
		{
			auto it = std::find_if(m_container.begin(), m_container.end(),
								   [PID](const CProcess& proc)
			{
				unsigned val;
				return  proc.GetPID(val) ? val == PID : false;
			});

			if (it == m_container.end())
			{
				CProcess temp(PID, m_processors_count, m_count_type);
				if (temp.Initialize())
				{
					m_container.push_back(std::move(temp));
				}
			}
			else
			{
				if (!it->TryToUpdateCurrentStatus())
				{
					m_container.erase(it);
				}
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

bool CContainerOfProcesses::GetAllProcesses(std::vector<CProcess>& to_vector)
{
	if (m_is_initialized)
	{
		to_vector = m_container;
		return true;
	}
	return false;
};