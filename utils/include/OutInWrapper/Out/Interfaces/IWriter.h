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
};
