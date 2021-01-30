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
	virtual bool WriteLine(bool value) = 0;
	virtual bool WriteLine(short value) = 0;
	virtual bool WriteLine(int value) = 0;
	virtual bool WriteLine(long value) = 0;
	virtual bool WriteLine(long long value) = 0;
	virtual bool WriteLine(unsigned short value) = 0;
	virtual bool WriteLine(unsigned value) = 0;
	virtual bool WriteLine(unsigned long value) = 0;
	virtual bool WriteLine(unsigned long long value) = 0;
	virtual bool WriteLine(float value) = 0;
	virtual bool WriteLine(double value) = 0;
	virtual bool WriteLine(long double value) = 0;
	virtual bool WriteLine(const char* value) = 0;
	virtual bool WriteLine(const std::string& value) = 0;
};
