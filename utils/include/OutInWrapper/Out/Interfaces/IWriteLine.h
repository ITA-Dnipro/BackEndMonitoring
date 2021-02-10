#pragma once
#include <string>

struct IWriteLine
{
	IWriteLine() = default;
	IWriteLine(const IWriteLine&) = delete;
	IWriteLine(IWriteLine&&) noexcept = default;

	virtual ~IWriteLine() = default;

	IWriteLine& operator=(const IWriteLine&) = delete;
	IWriteLine& operator=(IWriteLine&&) noexcept = default;
	
	virtual bool WriteLine(char value) = 0;
	virtual bool WriteLine(const std::string& value) = 0;
};
