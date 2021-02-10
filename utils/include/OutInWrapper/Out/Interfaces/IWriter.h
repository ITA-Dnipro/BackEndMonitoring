#pragma once
#include "IBreakLine.h"
#include "IWrite.h"
#include "IWriteLine.h"

struct IWriter : public IWrite, public IWriteLine, public IBreakLine
{
	IWriter() = default;
	IWriter(const IWriter&) = delete;
	IWriter(IWriter&&) noexcept = default;

	IWriter& operator=(const IWriter&) = delete;
	IWriter& operator=(IWriter&&) noexcept = default;

	~IWriter() override = default;

	bool Write(char value) override = 0;
	bool Write(const std::string& value) override = 0;

	bool WriteLine(char value) override = 0;
	bool WriteLine(const std::string& value) override = 0;

	bool BreakLine() override = 0;
};
