#include "stdafx.h"

#include "ERequestRangeSpecification.h"
#include "CDataProvider.h"
#include "Utils.h"
#include "GlobalVariable.h"

#include "CRequestExcDiskData.h"

CRequestExcDiskData::CRequestExcDiskData(const std::string& request,
	std::shared_ptr<CDataProvider> data_base) :
	IRequestExc(request, data_base)
{ }

bool CRequestExcDiskData::Execute(std::string& answer)
{
	//do I need another validation????
	//validation  + boolean is valid
	nlohmann::json request = nlohmann::json::parse(m_request);

	switch (IsSpecial(request))
	{
	case ERequestRangeSpecification::LAST_DATA:
		answer = m_p_data_base->GetDisksLastInfo();
		return true;
	case ERequestRangeSpecification::ALL_DATA:
		answer = m_p_data_base->GetDisksFullInfo();
		return true;
	case ERequestRangeSpecification::RANGE_OF_DATA:
	{
		if (!TryDetermineDateRange(request))
		{
			return false;
		}
		time_t start{}, end{};
		if (!Utils::StringToDate(m_range_of_data[0],
			GlobalVariable::c_request_format_default, start) ||
			!Utils::StringToDate(m_range_of_data[1],
				GlobalVariable::c_request_format_default, start))
		{
			// log
			return false;
		}
		answer = m_p_data_base->GetDisksSelectedInfo(start, end);
	
		return true;
	}
	default:
		// log
		return false;
	}

	return false;
}