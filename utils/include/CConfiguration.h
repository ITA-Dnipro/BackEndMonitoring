#pragma once

#include "IParser.h"

class CConfiguration
{
public:
	CConfiguration() = delete;
	CConfiguration(CConfiguration&) = delete;
	CConfiguration(CConfiguration&&) = delete;

	CConfiguration(std::unique_ptr<IParser> p_parser);

	bool TryToGetConfiguration(const std::string& request,
		bool& return_data) const;
	bool TryToGetConfiguration(const std::string& request,
		int& return_data) const;
	bool TryToGetConfiguration(const std::string& request,
		std::string& return_data) const;

private:
	std::unique_ptr<IParser> p_parser_;
};