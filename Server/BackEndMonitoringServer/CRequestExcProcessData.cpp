#include "stdafx.h"
#include "CRequestExcProcessData.h"

CRequestExcProcessData::CRequestExcProcessData(const std::string& request) :
    IRequestExc(request)
{ }

bool CRequestExcProcessData::Execute(std::string& answer)
{
	//do I need another validation????
	nlohmann::json request = nlohmann::json::parse(m_request);

	if (!DetermineDateRange(request))
	{
		//to log
		return false;
	}

	return false;
}