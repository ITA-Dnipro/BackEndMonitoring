#include "stdafx.h"

#include "ERequestRangeSpecification.h"
#include "Utils.h"
#include "CDataProvider.h"
#include "GlobalVariable.h"
#include "CResponseFrame.h"
#include "EResponseError.h"

#include "CRequestExcProcessData.h"

CRequestExcProcessData::CRequestExcProcessData(const std::string& request,
	std::shared_ptr<CDataProvider> data_base) :
    IRequestExc(request, data_base)
{ }

bool CRequestExcProcessData::Execute(std::string& answer)
{
	//do I need another validation????
	nlohmann::json request = nlohmann::json::parse(m_request);
	CResponseFrame response(request[GlobalVariable::c_request_key_id]);

	switch (IsSpecial(request))
	{
	case ERequestRangeSpecification::LAST_DATA:
		answer = m_p_data_base->GetProcessesLastInfo();
		return true;
	case ERequestRangeSpecification::ALL_DATA:
		answer = m_p_data_base->GetProcessesFullInfo();
		return true;
	case ERequestRangeSpecification::RANGE_OF_DATA:
	{
		if (!TryDetermineDateRange(request))
		{
			response.TryFormateResponse(answer, "",
				EResponseError::INCORRECT_REQUEST);
			return false;
		}
		time_t start{}, end{};
		if (!Utils::StringToDate(m_range_of_data[0],
			GlobalVariable::c_request_format_default, start) ||
			!Utils::StringToDate(m_range_of_data[1],
				GlobalVariable::c_request_format_default, end))
		{
			response.TryFormateResponse(answer, "",
				EResponseError::INCORRECT_REQUEST);
			return false;
		}
		answer = m_p_data_base->GetProcessesSelectedInfo(start, end);

		return true;
	}
	default:
		response.TryFormateResponse(answer, "",
			EResponseError::INCORRECT_REQUEST);
		return false;
	}

	response.TryFormateResponse(answer, "",
		EResponseError::INCORRECT_REQUEST);
	return false;
}