#include "stdafx.h"

#include "EMemoryConvertType.h"
#include "PlatformUtils.h"
#include "CLogger/include/Log.h"
#include "Utils.h"

#include "CProcessInfo.h"

CProcessInfo::CProcessInfo(unsigned PID,
                           EMemoryConvertType type) :
    m_PID(PID),m_count_type(type), 
    m_cpu_usage(0.0), m_ram_usage(0ULL), m_pagefile_usage(0ULL),
    m_last_sys_time(0ULL), m_last_kernel_time(0ULL), m_last_user_time(0ULL),
    m_is_initialized(false)
{ 
    CLOG_TRACE("Process " + std::to_string(m_PID) + " created");
}

CProcessInfo::CProcessInfo(const CProcessInfo& other) : m_PID(other.m_PID), 
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type),
        m_last_kernel_time(other.m_last_kernel_time),
        m_last_sys_time(other.m_last_sys_time),
        m_last_user_time(other.m_last_user_time),
        m_is_initialized(other.m_is_initialized)
{ 
    CLOG_TRACE("Process " + std::to_string(m_PID) + " created using copy c-tor");
}

CProcessInfo::CProcessInfo(CProcessInfo&& other) noexcept: m_PID(other.m_PID),
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type),
        m_last_kernel_time(other.m_last_kernel_time),
        m_last_sys_time(other.m_last_sys_time),
        m_last_user_time(other.m_last_user_time),
        m_is_initialized(other.m_is_initialized)
{ 
    CLOG_TRACE("Process " + std::to_string(m_PID) + " created using move c-tor");
}

CProcessInfo& CProcessInfo::operator=(const CProcessInfo& other)
{
    CLOG_TRACE("Process " + std::to_string(other.m_PID) + " asigned to process "
               + std::to_string(m_PID) + "using operator=");

    m_PID = other.m_PID;
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

bool CProcessInfo::Initialize()
{
    CLOG_TRACE_START_FUNCTION( );

    if(m_is_initialized)
    { 
        CLOG_PROD("WARNING!!! Called initialize on already initialized process");
        return false;
    }
 
    bool success = PlatformUtils::GetProcessTimes(m_PID, m_last_sys_time,
                                                 m_last_kernel_time,
                                                 m_last_user_time);
    if (!success)
    {
        CLOG_PROD("WARNING!!! Can't get process times for PID: " +
                  std::to_string(m_PID));
        return success;
    }

    success = PlatformUtils::GetProcessMemoryUsage(m_PID, m_ram_usage, 
                                                   m_pagefile_usage);
    if (!success)
    {
        CLOG_PROD("WARNING!!! Can't get memory usage for PID: " +
                  std::to_string(m_PID));
    }

    if (m_is_initialized = success)
    {
        CLOG_TRACE("Process " + std::to_string(m_PID) + "was isitialized");
    }
    else
    {
        CLOG_DEBUG("Process " + std::to_string(m_PID) + "wasn't isitialized");
    }
    CLOG_TRACE_END_FUNCTION( );
    return m_is_initialized;
}

bool CProcessInfo::TryToUpdateCurrentStatus()
{
    bool success = true;
    CLOG_TRACE_START_FUNCTION( );
    if(!m_is_initialized)
    { 
        CLOG_PROD("ERROR!!! Called function on non initialized process");
        return false;
    }

    if (success = CountCpuUsage( ))
    {
        CLOG_TRACE("CPU usage of process " + std::to_string(m_PID) + " counted successfully");
    }
    else
    {
        CLOG_DEBUG("Failed to count CPU usage of process " + std::to_string(m_PID));
        return success;
    }

    success = PlatformUtils::GetProcessMemoryUsage(m_PID, m_ram_usage,
                                                   m_pagefile_usage);
    if (success)
    {
        CLOG_TRACE("Memory usage of process " + std::to_string(m_PID) + " counted successfully");
    }
    else
    {
        CLOG_DEBUG("Failed to count memory usage of process " + std::to_string(m_PID));
    }

    CLOG_TRACE_END_FUNCTION( );
    return success;
}

bool CProcessInfo::IsActive() const
{
    CLOG_TRACE_START_FUNCTION( );
    if (!m_is_initialized)
    {
        CLOG_PROD("ERROR!!! Called function on non initialized process");
        return false;
    }
    CLOG_TRACE_END_FUNCTION( );
    return PlatformUtils::CheckIsProcessActive(m_PID);
}

bool CProcessInfo::GetPID(unsigned& value) const
{   
    CLOG_TRACE_START_FUNCTION( );
    if (m_is_initialized)
    {
        value = m_PID;
        CLOG_TRACE_VAR_CREATION(value);
    }
    else
    {
        CLOG_PROD("ERROR!!! Called function on non initialized process");
    }
    CLOG_TRACE_END_FUNCTION( );
    return m_is_initialized;
}

bool CProcessInfo::GetCpuUsage(double& value) const
{
    CLOG_TRACE_START_FUNCTION( );
    if (m_is_initialized)
    {
        value = Utils::RoundToDecimal(m_cpu_usage);
        CLOG_TRACE_VAR_CREATION(value);
    }
    else
    {
        CLOG_PROD("ERROR!!! Called function on non initialized process");
    }
    CLOG_TRACE_END_FUNCTION( );
    return m_is_initialized;
}

bool CProcessInfo::GetRamUsage(long double& value) const
{
    CLOG_TRACE_START_FUNCTION( );
    if (m_is_initialized)
    {
        value = Utils::RoundToDecimal(
            Utils::ConvertToCountType(m_ram_usage, m_count_type));
        CLOG_TRACE_VAR_CREATION(value);
    }
    else
    {
        CLOG_PROD("ERROR!!! Called function on non initialized process");
    }
    CLOG_TRACE_END_FUNCTION( );
    return m_is_initialized;
}

bool CProcessInfo::GetPagefileUsage(long double& value) const
{
    CLOG_TRACE_START_FUNCTION( );
    if (m_is_initialized)
    {
        value = Utils::RoundToDecimal(
            Utils::ConvertToCountType(m_pagefile_usage, m_count_type));
        CLOG_TRACE_VAR_CREATION(value);
    }
    else
    {
        CLOG_PROD("ERROR!!! Called function on non initialized process");
    }
    CLOG_TRACE_END_FUNCTION( );
    return m_is_initialized;
}

EMemoryConvertType CProcessInfo::GetMemoryCountType() const
{
    CLOG_TRACE_START_FUNCTION( );
    CLOG_TRACE_END_FUNCTION( );
    return m_count_type;
}


bool CProcessInfo::CountCpuUsage()
{
    bool success = true;
    CLOG_TRACE_START_FUNCTION( );

    unsigned long long cur_sys_time = 0; 
    CLOG_TRACE_VAR_CREATION(cur_sys_time);

    unsigned long long cur_kernel_time = 0;
    CLOG_TRACE_VAR_CREATION(cur_sys_time);

    unsigned long long cur_user_time = 0;
    CLOG_TRACE_VAR_CREATION(cur_sys_time);

    success = PlatformUtils::GetProcessTimes(m_PID, cur_sys_time,
                                             cur_kernel_time, cur_user_time);
    if (success)
    {
        CLOG_TRACE("Processor times of process " + std::to_string(m_PID) +
                    " getted successfully");
    }
    else
    {
        CLOG_PROD("WARNING!!! Can't Get process " + std::to_string(m_PID) +
                    " processor times");
        return success;
    }

    if (cur_sys_time <= m_last_sys_time)
    {
        CLOG_PROD("WARNING!!! System times of process " + std::to_string(m_PID)
                  + "is equal");
        CLOG_DEBUG("Sleep thread");
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        CLOG_DEBUG("Thread awaked");
        success = PlatformUtils::GetProcessTimes(m_PID, cur_sys_time,
                                                 cur_kernel_time, 
                                                 cur_user_time);
        if (success)
        {
            CLOG_TRACE("Processor times of process " + std::to_string(m_PID) +
                       " getted successfully");
        }
        else
        {
            CLOG_PROD("WARNING!!! Can't Get process " + std::to_string(m_PID) +
                      " processor times");
            return success;
        }
    }

    size_t kernel_div = (cur_kernel_time - m_last_kernel_time);
    CLOG_TRACE_VAR_CREATION(kernel_div);
    size_t user_div = (cur_user_time - m_last_user_time);
    CLOG_TRACE_VAR_CREATION(user_div);

    m_cpu_usage = (
                    static_cast<double>(kernel_div + user_div)
                    /
                    static_cast<double>(cur_sys_time - m_last_sys_time)
                  ) * 100;
    CLOG_TRACE_VAR_CREATION(m_cpu_usage);

    m_last_sys_time = cur_sys_time;
    CLOG_TRACE_VAR_CREATION(m_last_sys_time);
    m_last_kernel_time = cur_kernel_time;
    CLOG_TRACE_VAR_CREATION(m_last_kernel_time);
    m_last_user_time = cur_user_time;
    CLOG_TRACE_VAR_CREATION(m_last_user_time);

    CLOG_TRACE_END_FUNCTION( );
    return success;
}


