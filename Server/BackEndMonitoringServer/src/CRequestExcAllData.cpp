#include "stdafx.h"

#include "IRequestExc.h"

#include "CRequestExcAllData.h"

CRequestExcAllData::CRequestExcAllData(const std::string& request) : 
	IRequestExc(request)
{ }

bool CRequestExcAllData::Execute(std::string & answer)
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
