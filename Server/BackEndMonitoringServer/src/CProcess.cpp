#include "stdafx.h"

#include "EMemoryCountType.h"
#include "PlatformUtils.h"
#include "CProcess.h"

CProcess::CProcess(unsigned PID, unsigned count_of_processors, 
                   EMemoryCountType type) :
    m_PID(PID),
    m_count_of_processors(count_of_processors),m_count_type(type), 
    m_cpu_usage(0.0), m_ram_usage(00ULL), m_pagefile_usage(00ULL),
    m_last_sys_time(0ULL), m_last_kernel_time(0ULL), m_last_user_time(0ULL),
    m_is_initialized(false)
{ }

CProcess::CProcess(const CProcess& other) : m_PID(other.m_PID), 
        m_count_of_processors(other.m_count_of_processors),
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type),
        m_last_kernel_time(other.m_last_kernel_time),
        m_last_sys_time(other.m_last_sys_time),
        m_last_user_time(other.m_last_user_time),
        m_is_initialized(other.m_is_initialized)
{ }

CProcess::CProcess(CProcess&& other) noexcept: m_PID(other.m_PID),
        m_count_of_processors(other.m_count_of_processors),
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type),
        m_last_kernel_time(other.m_last_kernel_time),
        m_last_sys_time(other.m_last_sys_time),
        m_last_user_time(other.m_last_user_time),
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
    m_last_kernel_time = other.m_last_kernel_time;
    m_last_sys_time = other.m_last_sys_time;
    m_last_user_time = other.m_last_user_time;
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
    
    success = PlatformUtils::GetProcessTimes(m_PID, m_last_sys_time, 
                                             m_last_kernel_time,
                                             m_last_user_time);
    if (!success)
    { return success;}

    success = PlatformUtils::GetProcessMemoryUsage(m_PID, m_ram_usage, 
                                                   m_pagefile_usage);
    m_is_initialized = success;
    return success;
}

bool CProcess::TryToUpdateCurrentStatus()
{
    if(!m_is_initialized)
    {
        return false;
    }
    bool success;

    success = ComputeCpuUsage();
    if (!success)
    { return success;}

    success = PlatformUtils::GetProcessMemoryUsage(m_PID, m_ram_usage,
                                                   m_pagefile_usage);
    return success;
}

bool CProcess::IsActive() const
{
    if (!m_is_initialized)
    {
        return false;
    }

    return PlatformUtils::CheckIsProcessActive(m_PID);
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


bool CProcess::ComputeCpuUsage()
{
    bool success;

    unsigned long long cur_sys_time, cur_kernel_time, cur_user_time;
    cur_sys_time = cur_kernel_time = cur_user_time = 0;
    success = PlatformUtils::GetProcessTimes(m_PID, cur_sys_time,
                                             cur_kernel_time, cur_user_time);
    if (!success)
    { return success;}

    if (cur_sys_time <= m_last_sys_time)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        success = PlatformUtils::GetProcessTimes(m_PID, cur_sys_time,
                                                 cur_kernel_time, cur_user_time);
        if (!success)
        { return success;}
    }

    size_t kernel_div = (cur_kernel_time - m_last_kernel_time);
    size_t user_div = (cur_user_time - m_last_user_time);

    m_cpu_usage = (
                    static_cast<double>(kernel_div + user_div)
                    /
                    static_cast<double>(cur_sys_time - m_last_sys_time)
                  ) * 100;
    m_cpu_usage /= m_count_of_processors;

    m_last_sys_time = cur_sys_time;
    m_last_kernel_time = cur_kernel_time;
    m_last_user_time = cur_user_time;

    return success;
}


