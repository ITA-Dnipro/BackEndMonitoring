#pragma once

class CEvent;

class IHardwareInfoMonitoring
{
public:
	IHardwareInfoMonitoring() = delete;
	explicit IHardwareInfoMonitoring(CEvent& stop_event) : 
		m_stop_event(stop_event)
	{ };
	IHardwareInfoMonitoring(const IHardwareInfoMonitoring& orig) = delete;
	IHardwareInfoMonitoring(const IHardwareInfoMonitoring&&) = delete;
	/// <summary>
	/// What threade will be doing. Containe data check logic inside of
	/// infinite loop with timer.
	/// </summary>
	/// <returns></returns>
	virtual bool StartMonitoringInfo ( ) = 0;

protected:
	CEvent& m_stop_event;
};

