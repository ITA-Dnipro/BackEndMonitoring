#include "stdafx.h"

#include "EMemoryCountType.h"
#include "CProcess.h"

CProcess::CProcess(unsigned PID, unsigned count_of_processors, 
                   EMemoryCountType type) :
    m_PID(PID),
    m_count_of_processors(count_of_processors),
    m_count_type(type), m_cpu_usage(0), m_ram_usage(0), m_pagefile_usage(0),
    last_sys_time{0, 0}, last_kernel_time{ 0, 0 }, last_user_time{ 0, 0 },
    m_is_initialized(false)
{ }

CProcess::CProcess(const CProcess& other) : m_PID(other.m_PID), 
        m_count_of_processors(other.m_count_of_processors),
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type),
        last_kernel_time(other.last_kernel_time),
        last_sys_time(other.last_sys_time),
        last_user_time(other.last_user_time)
{ }

CProcess::CProcess(CProcess&& other) noexcept: m_PID(other.m_PID),
        m_count_of_processors(other.m_count_of_processors),
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type),
        last_kernel_time(other.last_kernel_time),
        last_sys_time(other.last_sys_time),
        last_user_time(other.last_user_time),
        m_is_initialized(other.m_is_initialized)
{ }

CProcess& CProcess::operator=(const CProcess& other)
{
    m_PID = other.m_PID;
    m_count_of_processors = other.m_count_of_processors;
    m_cpu_usage = other.m_cpu_usage;
    m_ram_usage = other.m_ram_usage;
    m_pagefile_usage = other.m_pagefile_usage;
    m_count_type = other.m_count_type;
    last_kernel_time = other.last_kernel_time;
    last_sys_time = other.last_sys_time;
    last_user_time = other.last_user_time;
    m_is_initialized = other.m_is_initialized;
    return *this;
}

bool CProcess::Initialize()
{
    if(m_is_initialized)
    {
        return false;
    }
    bool success;
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
        FALSE, m_PID);
    if (success = (process != 0))
    {
        FILETIME ftime, fsys, fuser;
        GetSystemTimeAsFileTime(&ftime);
        memcpy(&last_sys_time, &ftime, sizeof(FILETIME));

        GetProcessTimes(process, &ftime, &ftime, &fsys, &fuser);
        memcpy(&last_kernel_time, &fsys, sizeof(FILETIME));
        memcpy(&last_user_time, &fuser, sizeof(FILETIME));
        CloseHandle(process);
    }
    m_is_initialized = true;
    return success;
}

bool CProcess::TryToUpdateCurrentStatus()
{
    if(!m_is_initialized)
    {
        return false;
    }
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
                                 FALSE, m_PID);

    bool success = (NULL != process);
    if (success) {
        ComputeCpuUsage(process);
        SetMemoryUsage(process);
        CloseHandle(process);
    }
    return success;
}

bool CProcess::IsActive() const
{
    if (!m_is_initialized)
    {
        return false;
    }
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,
                                 FALSE, m_PID);

    bool success;
    if (success = (process != 0))
    {
        CloseHandle(process);
    }
    return success;
}

bool CProcess::GetPID(unsigned& value) const
{   
    if (m_is_initialized)
    {
        value = m_PID;
        return true;
    }
    return false;
}

bool CProcess::GetCpuUsage(double& value) const
{
    if (m_is_initialized)
    {
        value = m_cpu_usage;
        return true;
    }
    return false;
}

bool CProcess::GetRamUsage(long double& value) const
{
    if (m_is_initialized)
    {
        value = static_cast<long double>(m_ram_usage)
                /
                static_cast<unsigned>(m_count_type);
        return true;
    }
    return false;
}

bool CProcess::GetPagefileUsage(long double& value) const
{
    if (m_is_initialized)
    {
        value = static_cast<long double>(m_pagefile_usage)
                /
                static_cast<unsigned>(m_count_type);
        return true;
    }
    return false;
}

EMemoryCountType CProcess::GetMemoryCountType() const
{ return m_count_type;}


void CProcess::ComputeCpuUsage(const HANDLE& process)
{
    ULARGE_INTEGER sys_time, kernel_time, user_time;

    FILETIME ftime, fsys, fuser;
    GetSystemTimeAsFileTime(&ftime);
    memcpy(&sys_time, &ftime, sizeof(FILETIME));

    GetProcessTimes(process, &ftime, &ftime, &fsys, &fuser);
    memcpy(&kernel_time, &fsys, sizeof(FILETIME));
    memcpy(&user_time, &fuser, sizeof(FILETIME));

    if (sys_time.QuadPart <= last_sys_time.QuadPart)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        GetSystemTimeAsFileTime(&ftime);
        memcpy(&sys_time, &ftime, sizeof(FILETIME));
    }

    size_t kern_div = (kernel_time.QuadPart - last_kernel_time.QuadPart);
    size_t usr_div = (user_time.QuadPart - last_user_time.QuadPart);

    m_cpu_usage = (
                    static_cast<double>(kern_div + usr_div)
                    /
                    static_cast<double>(sys_time.QuadPart - last_sys_time.QuadPart)
                  ) * 100;
    m_cpu_usage /= m_count_of_processors;

    last_sys_time = sys_time;
    last_kernel_time = kernel_time;
    last_user_time = user_time;
}

void CProcess::SetMemoryUsage(const HANDLE& process)
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
    m_pagefile_usage = pmc.PagefileUsage;
    m_ram_usage = pmc.WorkingSetSize;
}


