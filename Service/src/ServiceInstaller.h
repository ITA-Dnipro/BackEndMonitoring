#pragma once
#include "BMService.h"

namespace ServiceInstaller 
{
	
bool Install(const BMService& service);
bool Uninstall(const BMService& service);

};
