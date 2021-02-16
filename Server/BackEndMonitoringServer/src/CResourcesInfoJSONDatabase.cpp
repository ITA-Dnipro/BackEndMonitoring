#include "stdafx.h"

#include "CResourcesInfoJSONDatabase.h"

bool CResourcesInfoJSONDatabase::InsertData(double cpu_usage, double ram_usage, double pagefile_usage)
{
	return false;
}

bool CResourcesInfoJSONDatabase::GetAllInfo(std::string& data)
{
	return false;
}

bool CResourcesInfoJSONDatabase::GetLastInfo(std::string& data)
{
	return false;
}

bool CResourcesInfoJSONDatabase::GetSelectedInfo(time_t from, time_t to, std::string& data)
{
	return false;
}
