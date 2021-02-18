#include "stdafx.h"
#include "CRequestExcDiskData.h"

CRequestExcDiskData::CRequestExcDiskData(const std::string& request) :
	IRequestExc(request)
{ }

bool CRequestExcDiskData::Execute(std::string & answer)
{
	//do I need another validation????
	//validation  + boolean is valid
	nlohmann::json request = nlohmann::json::parse(m_request);
	
	if (!DetermineDateRange(request))
	{
		//to log
		return false;
	}
	
	return false;
}