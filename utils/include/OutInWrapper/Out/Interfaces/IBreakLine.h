#pragma once

struct IBreakLine {
	IBreakLine() = default;
	IBreakLine(const IBreakLine&) = delete;
	IBreakLine(IBreakLine&&) noexcept = default;

	virtual ~IBreakLine() = default;

	IBreakLine& operator=(const IBreakLine&) = delete;
	IBreakLine& operator=(IBreakLine&&) noexcept = default;
	
	virtual bool BreakLine() = 0;
};