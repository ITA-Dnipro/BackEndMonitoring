#pragma once
#include <string>

struct IReader
{
	IReader() = default;
	IReader(const IReader&) = delete;
	IReader(IReader&&) noexcept = default;

	IReader& operator=(const IReader&) = delete;
	IReader& operator=(IReader&&) noexcept = default;

	virtual ~IReader() = default;

	virtual bool Read(char& value) = 0;
	virtual bool Read(std::string& value) = 0;

	virtual bool ReadLine(std::string& value) = 0;
};
