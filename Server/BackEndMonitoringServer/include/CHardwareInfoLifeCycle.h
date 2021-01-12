#pragma once

#include "ÑHardwareStatusSpecification.h"

class CHardwareInfoLifeCycle
{
public:
	// todo: add as param specificator-class
	/// <summary>
	/// What threade will be doing. Containe data check logic inside of
	/// infinite loop with timer.
	/// </summary>
	/// <returns></returns>
	virtual void ThreadLifeCycle( ) = 0;
};

