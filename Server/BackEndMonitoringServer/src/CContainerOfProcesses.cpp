#include "stdafx.h"

#include "CProcessInfo.h"
#include "CContainerOfProcesses.h"
#include "PlatformUtils.h"

CContainerOfProcesses::CContainerOfProcesses(std::chrono::duration<int> 
	pause_duration, std::string path_to_file, EMemoryConvertType count_type) :
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
	bool success = true;
	if (success = PlatformUtils::GetListOfProcessIds(list_of_PIDs))
	{
		for (auto PID : list_of_PIDs)
		{
			CProcessInfo temp(PID, m_processors_count, m_count_type);
			success = temp.Initialize();
			if (success = temp.TryToUpdateCurrentStatus())
			{
				m_container.push_back(std::move(temp));
			}
		}
	}
	m_is_initialized = success;
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
								   [PID](const CProcessInfo& proc)
			{
				unsigned val;
				return  proc.GetPID(val) ? val == PID : false;
			});

			if (it == m_container.end())
			{
				CProcessInfo temp(PID, m_processors_count, m_count_type);
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
										 [](const CProcessInfo& proc)
		{
			return !proc.IsActive();
		});

		while (dead_process != m_container.end())
		{
			m_container.erase(dead_process);
			dead_process = std::find_if(m_container.begin(), m_container.end(),
									    [](const CProcessInfo& proc)
			{
				return !proc.IsActive();
			});
		}
	}
	return success;
}

bool CContainerOfProcesses::GetAllProcesses(std::vector<CProcessInfo>& to_vector)
{
	if (m_is_initialized)
	{
		to_vector = m_container;
	}
	return m_is_initialized;
};