#include "stdafx.h"

#include <psapi.h>

#include "EConvertValueFromBytes.h"

#include "CProcess.h"

CProcess::CProcess(unsigned PID, unsigned count_of_processors, 
                   EMemoryCountType type) :
    m_PID(PID),
    m_count_of_processors(count_of_processors),
    m_count_type(type)
{ }

CProcess::CProcess(const CProcess& other) : m_PID(other.m_PID), 
        m_count_of_processors(other.m_count_of_processors),
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type)
{ }

CProcess::CProcess(CProcess&& other) noexcept: m_PID(other.m_PID),
        m_count_of_processors(other.m_count_of_processors),
        m_cpu_usage(other.m_cpu_usage),
        m_ram_usage(other.m_ram_usage),
        m_pagefile_usage(other.m_pagefile_usage),
        m_count_type(other.m_count_type)
{ }

CProcess& CProcess::operator=(const CProcess& other)
{
    m_PID = other.m_PID;
    m_count_of_processors = other.m_count_of_processors;
    m_cpu_usage = other.m_cpu_usage;
    m_ram_usage = other.m_ram_usage;
    m_pagefile_usage = other.m_pagefile_usage;
    m_count_type = other.m_count_type;
    return *this;
}

bool CProcess::TryToUpdateCurrentStatus()
{
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
    HANDLE process = OpenProcess(PROCESS_QUERY_INFORMATION |PROCESS_VM_READ,
                                 FALSE, m_PID);

    bool success = (NULL != process);
    if (success)
    {
        CloseHandle(process);
    }
    return success;
}

unsigned CProcess::GetPID() const
{ return m_PID;}

double CProcess::GetCpuUsage() const
{ return m_cpu_usage;}

long double CProcess::GetRamUsage() const
{
    switch (m_count_type)
    {
    case (EMemoryCountType::BYTES):
        return static_cast<long double>(m_ram_usage);
    case (EMemoryCountType::MEGABYTES):
        return static_cast<long double>(m_ram_usage) /
               static_cast<int>(EConvertValueFromBytes::INTO_MEGABYTES);
    case (EMemoryCountType::GIGABYTES):
        return static_cast<long double>(m_ram_usage) /
               static_cast<int>(EConvertValueFromBytes::INTO_GIGABYTES);
    default:
        return static_cast<long double>(m_ram_usage);
    }
}

long double CProcess::GetPagefileUsage() const
{
    switch (m_count_type)
    {
    case (EMemoryCountType::BYTES):
        return static_cast<long double>(m_pagefile_usage);
    case (EMemoryCountType::MEGABYTES):
        return static_cast<long double>(m_pagefile_usage) /
            static_cast<int>(EConvertValueFromBytes::INTO_MEGABYTES);
    case (EMemoryCountType::GIGABYTES):
        return static_cast<long double>(m_pagefile_usage) /
            static_cast<int>(EConvertValueFromBytes::INTO_GIGABYTES);
    default:
        return static_cast<long double>(m_pagefile_usage);
    }
}

EMemoryCountType CProcess::GetMemoryCountType() const
{ return m_count_type;}


void CProcess::ComputeCpuUsage(const HANDLE& process)
{
    ULARGE_INTEGER system_time[2], kernel_cpu_time[2], user_cpu_time[2];

    for (unsigned short i = 0; i < 2; ++i) {
        FILETIME ftime, fsys, fuser;
        GetSystemTimeAsFileTime(&ftime);
        memcpy(&system_time[i], &ftime, sizeof(FILETIME));

        GetProcessTimes(process, &ftime, &ftime, &fsys, &fuser);
        memcpy(&kernel_cpu_time[i], &fsys, sizeof(FILETIME));
        memcpy(&user_cpu_time[i], &fuser, sizeof(FILETIME));
        Sleep(1);
    }

    m_cpu_usage = static_cast<double>(
                  (kernel_cpu_time[1].QuadPart - kernel_cpu_time[0].QuadPart) +
                  (user_cpu_time[1].QuadPart - user_cpu_time[0].QuadPart));
    m_cpu_usage /= (system_time[1].QuadPart - system_time[0].QuadPart);
    m_cpu_usage /= m_count_of_processors;
    m_cpu_usage *= 100;
}

void CProcess::SetMemoryUsage(const HANDLE& process)
{
    PROCESS_MEMORY_COUNTERS pmc;
    GetProcessMemoryInfo(process, &pmc, sizeof(pmc));
    m_pagefile_usage = pmc.PagefileUsage;
    m_ram_usage = pmc.WorkingSetSize;
}


