#pragma once

enum class EMemoryCountType;

class CProcess {
public:
	CProcess() = default;
	explicit CProcess(unsigned PID, unsigned count_of_processors, 
		     EMemoryCountType type);
	CProcess(const CProcess&);
	CProcess(CProcess&&) noexcept;
	CProcess& operator= (const CProcess&);

	bool Initialize();
	bool TryToUpdateCurrentStatus();
	bool IsActive() const;
	bool GetPID(unsigned&) const;
	bool GetCpuUsage(double&) const;
	bool GetRamUsage(long double&) const;
	bool GetPagefileUsage(long double&) const;
	EMemoryCountType GetMemoryCountType() const;
private:
	void ComputeCpuUsage(const HANDLE& process);
	void SetMemoryUsage(const HANDLE& process);

private:
	bool m_is_initialized;
	unsigned m_PID;
	unsigned m_count_of_processors;
	double m_cpu_usage;
	size_t m_ram_usage;
	size_t m_pagefile_usage;
	EMemoryCountType m_count_type;
	ULARGE_INTEGER last_sys_time, last_kernel_time, last_user_time;
};

