#include "stdafx.h"

#include "Utils.h"

#define EN_US 0x0409

void Utils::DisplayError(const std::string& message)
{
	// char*
	LPSTR error = NULL;

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		GetLastError(),
		EN_US,
		reinterpret_cast<LPSTR>(&error),
		0, 
		NULL);

	std::cout << message << ". " << error;
	LocalFree(error);
}

void Utils::DisplayMessage(const std::string& message)
{
	std::cout << message << ". " << std::endl;
}
