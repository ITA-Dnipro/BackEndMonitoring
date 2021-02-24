#pragma once

enum class EMemoryConvertType;

class CProcessInfo {
public:
	CProcessInfo() = default;
	explicit CProcessInfo(unsigned PID,  EMemoryConvertType type);
	CProcessInfo(const CProcessInfo&);
	CProcessInfo(CProcessInfo&&) noexcept;
	CProcessInfo& operator= (const CProcessInfo&);

	bool Initialize();
	bool TryToUpdateCurrentStatus();
	bool IsActive() const;
	bool GetPID(unsigned&) const;
	bool GetCpuUsage(double&) const;
	bool GetRamUsage(long double&) const;
	bool GetPagefileUsage(long double&) const;
	EMemoryConvertType GetMemoryCountType() const;
private:
	bool CountCpuUsage();

private:
	double m_cpu_usage;
	unsigned long long m_ram_usage, m_pagefile_usage;
	unsigned long long m_last_sys_time, m_last_kernel_time, m_last_user_time;
	unsigned m_PID;
	EMemoryConvertType m_count_type;
	bool m_is_initialized;
};

