#pragma once
#include "IRead.h"
#include "IReadLine.h"

struct IReader : public IRead, public IReadLine
{
	IReader() = default;
	IReader(const IReader&) = delete;
	IReader(IReader&&) noexcept = default;

	IReader& operator=(const IReader&) = delete;
	IReader& operator=(IReader&&) noexcept = default;

	~IReader() override = default;

	bool Read(char& value) override = 0;
	bool Read(std::string& value) override = 0;

	bool ReadLine(std::string& value) override = 0;
};
