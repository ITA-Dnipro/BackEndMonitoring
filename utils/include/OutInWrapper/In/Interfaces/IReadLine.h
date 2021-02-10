#pragma once
#include <string>

struct IReadLine
{
	IReadLine() = default;
	IReadLine(const IReadLine&) = delete;
	IReadLine(IReadLine&&) noexcept = default;

	virtual ~IReadLine() = default;

	virtual bool ReadLine(std::string& value) = 0;
};
