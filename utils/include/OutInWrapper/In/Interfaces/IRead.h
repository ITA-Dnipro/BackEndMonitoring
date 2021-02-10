#pragma once
#include <string>

struct IRead
{
	IRead() = default;
	IRead(const IRead&) = delete;
	IRead(IRead&&) noexcept = default;

	virtual ~IRead() = default;

	virtual bool Read(char& value) = 0;
	virtual bool Read(std::string& value) = 0;
};
