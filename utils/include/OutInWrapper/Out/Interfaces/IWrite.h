#pragma once
#include <string>

struct IWrite
{
	IWrite() = default;
	IWrite(const IWrite&) = delete;
	IWrite(IWrite&&) noexcept = default;

	virtual ~IWrite() = default;

	IWrite& operator=(const IWrite&) = delete;
	IWrite& operator=(IWrite&&) noexcept = default;
	
	virtual bool Write(char value) = 0;
	virtual bool Write(const std::string& value) = 0;
};
