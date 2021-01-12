#pragma once

#include "ÑHardwareStatusSpecification.h"
#include "CEvent.h"

class CHardwareInfoLifeCycle
{
public:
	CHardwareInfoLifeCycle() = delete;
	CHardwareInfoLifeCycle(CEvent& stop_event) : m_stop_event(stop_event)
	{ };
	CHardwareInfoLifeCycle(const CHardwareInfoLifeCycle& orig) = delete;
	CHardwareInfoLifeCycle(const CHardwareInfoLifeCycle&&) = delete;
	// todo: add as param specificator-class
	/// <summary>
	/// What threade will be doing. Containe data check logic inside of
	/// infinite loop with timer.
	/// </summary>
	/// <returns></returns>
	virtual void ThreadLifeCycle( ) = 0;

protected:
	CEvent& m_stop_event;
};

