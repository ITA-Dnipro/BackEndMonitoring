#pragma once
#include <string>

struct IWrite {
	IWrite() = default;
	IWrite(const IWrite&) = delete;
	IWrite(IWrite&&) noexcept = default;

	virtual ~IWrite() = default;

	IWrite& operator=(const IWrite&) = delete;
	IWrite& operator=(IWrite&&) noexcept = default;
	
	virtual bool Write(char value) = 0;
	virtual bool Write(bool value) = 0;
	virtual bool Write(short value) = 0;
	virtual bool Write(int value) = 0;
	virtual bool Write(long value) = 0;
	virtual bool Write(long long value) = 0;
	virtual bool Write(unsigned short value) = 0;
	virtual bool Write(unsigned value) = 0;
	virtual bool Write(unsigned long value) = 0;
	virtual bool Write(unsigned long long value) = 0;
	virtual bool Write(float value) = 0;
	virtual bool Write(double value) = 0;
	virtual bool Write(long double value) = 0;
	virtual bool Write(const char* value) = 0;
	virtual bool Write(const std::string& value) = 0;
};
