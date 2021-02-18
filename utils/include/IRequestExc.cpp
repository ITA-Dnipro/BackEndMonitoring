#include "stdafx.h"

#include "ERequestRangeSpecification.h"

#include "IRequestExc.h"

IRequestExc::IRequestExc(const std::string& request) : m_request(request),
	m_range_specification(ERequestRangeSpecification::NONE)
{ }

//set as nothrow and check is correct 
IRequestExc::IRequestExc(IRequestExc&& orig) : 
	m_request(orig.m_request), 
	m_range_of_data(std::move(orig.m_range_of_data)),
	m_range_specification(orig.m_range_specification)
{ }

bool IRequestExc::DetermineDateRange(const nlohmann::json& request)
{
	switch (IsSpecial(request))
	{
	case ERequestRangeSpecification::LAST_DATA:
		m_range_specification = ERequestRangeSpecification::LAST_DATA;
		return true;
	case ERequestRangeSpecification::ALL_DATA:
		m_range_specification = ERequestRangeSpecification::ALL_DATA;
		return true;
	case ERequestRangeSpecification::RANGE_OF_DATA:
		m_range_specification = ERequestRangeSpecification::RANGE_OF_DATA;
		for (const auto& [key, value] : request["dur"].items())
		{
			m_range_of_data.emplace_back(value);
		}
		return true;

	default:
		return false;
	}
}

ERequestRangeSpecification IRequestExc::IsSpecial(const nlohmann::json& request)
{
	return ERequestRangeSpecification(request["spec"]);
}
