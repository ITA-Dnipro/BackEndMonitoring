#pragma once
#include <string>

struct IWriter
{
	IWriter() = default;
	IWriter(const IWriter&) = delete;
	IWriter(IWriter&&) noexcept = default;

	IWriter& operator=(const IWriter&) = delete;
	IWriter& operator=(IWriter&&) noexcept = default;

	virtual ~IWriter() = default;

	virtual bool Write(char value) = 0;
	virtual bool Write(const std::string& value) = 0;

	virtual bool WriteLine(char value) = 0;
	virtual bool WriteLine(const std::string& value) = 0;

	virtual bool BreakLine() = 0;
};
