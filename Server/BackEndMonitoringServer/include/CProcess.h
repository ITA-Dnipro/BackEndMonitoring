#pragma once

#include <windows.h>
#include <psapi.h>
#include <functional>

#include "EMemoryCountType.h"
#include "EConvertValueFromBytes.h"

class CProcess {
public:
	CProcess() = default;
	CProcess(unsigned PID, unsigned count_of_processors, EMemoryCountType type);
	CProcess(const CProcess&);
	CProcess(CProcess&&) noexcept;
	CProcess& operator= (const CProcess&);

	bool TryToUpdateCurrentStatus();
	bool IsActive() const;
	unsigned GetPID() const;
	double GetCpuUsage() const;
	long double GetRamUsage() const;
	long double GetPagefileUsage() const;
	EMemoryCountType GetMemoryCountType() const;
private:
	void ComputeCpuUsage(const HANDLE& process);
	void SetMemoryUsage(const HANDLE& process);

private:
	unsigned m_PID;
	unsigned m_count_of_processors;
	double m_cpu_usage = 0;
	size_t m_ram_usage = 0;
	size_t m_pagefile_usage = 0;
	EMemoryCountType m_count_type;
};

