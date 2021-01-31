#pragma once
#include <string>

struct IRead
{
	IRead() = default;
	IRead(const IRead&) = delete;
	IRead(IRead&&) noexcept = default;

	virtual ~IRead() = default;

	virtual bool Read(char& value) = 0;
	virtual bool Read(bool& value) = 0;
	virtual bool Read(short& value) = 0;
	virtual bool Read(int& value) = 0;
	virtual bool Read(long& value) = 0;
	virtual bool Read(long long& value) = 0;
	virtual bool Read(unsigned short& value) = 0;
	virtual bool Read(unsigned& value) = 0;
	virtual bool Read(unsigned long& value) = 0;
	virtual bool Read(unsigned long long& value) = 0;
	virtual bool Read(float& value) = 0;
	virtual bool Read(double& value) = 0;
	virtual bool Read(long double& value) = 0;
	virtual bool Read(char* value) = 0;
	virtual bool Read(std::string& value) = 0;
};
