#include "stdafx.h"
#include "CConfiguration.h"

CConfiguration::CConfiguration(std::unique_ptr<IParser> p_parser)
{
	p_parser_ = std::move(p_parser);
}

bool CConfiguration::TryToGetConfiguration(const std::string& request, bool& return_data) const
{
	return p_parser_->TryToGetConfiguration(request, return_data);
}

bool CConfiguration::TryToGetConfiguration(const std::string& request, int& return_data) const
{
	return p_parser_->TryToGetConfiguration(request, return_data);;
}

bool CConfiguration::TryToGetConfiguration(const std::string& request, std::string& return_data) const
{
	return p_parser_->TryToGetConfiguration(request, return_data);;
}
