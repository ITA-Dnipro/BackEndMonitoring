#pragma once

#include "stdafx.h"
#include "HardwareStatusSpecification.h"

class HardwareInfoLifeCycle
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

