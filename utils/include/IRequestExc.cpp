#include "stdafx.h"

#include "ERequestRangeSpecification.h"
#include "CDataProvider.h"
#include "GlobalVariable.h"

#include "IRequestExc.h"

IRequestExc::IRequestExc(const std::string& request, 
	std::shared_ptr<CDataProvider> data_base) : 
	m_request(request),
	m_p_data_base(data_base),
	m_range_specification(ERequestRangeSpecification::LAST_DATA)
{ }

bool IRequestExc::TryDetermineDateRange(const nlohmann::json& request)
{
	for (const auto& [key, value] : 
		request[GlobalVariable::c_request_key_duration].items())
	{
		m_range_of_data.emplace_back(value);
	}
	return !m_range_of_data.empty();
}

ERequestRangeSpecification IRequestExc::IsSpecial(const nlohmann::json& request)
{
	return ERequestRangeSpecification(request[
		GlobalVariable::c_request_key_spec]);
}
