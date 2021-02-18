#include "stdafx.h"

#include "IRequestExc.h"

#include "CRequestExcAllData.h"

CRequestExcAllData::CRequestExcAllData(const std::string& request) : 
	IRequestExc(request)
{ }
// todo: ?????????????????????????????????????????
CRequestExcAllData::CRequestExcAllData(CRequestExcAllData && orig) :
	IRequestExc(std::move(orig))
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
