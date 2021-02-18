#include "stdafx.h"
#include "CRequestExcDiskData.h"

CRequestExcDiskData::CRequestExcDiskData(const std::string& request) :
	IRequestExc(request)
{ }

CRequestExcDiskData::CRequestExcDiskData(CRequestExcDiskData&& orig) :
	IRequestExc(std::move(orig))
{ }

bool CRequestExcDiskData::Execute(std::string & answer)
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