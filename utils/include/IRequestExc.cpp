#include "stdafx.h"

#include "ERequestRangeSpecification.h"

#include "IRequestExc.h"

IRequestExc::IRequestExc(const std::string& request) : m_request(request)
{ }

IRequestExc::IRequestExc(IRequestExc&& orig) : 
	m_request(std::move(orig.m_request))
{ }

bool IRequestExc::DetermineDateRange()
{
	switch (IsSpecial())
	{
	case ERequestRangeSpecification::LAST_DATA:
		m_range_specification = ERequestRangeSpecification::LAST_DATA;
		return true;
	case ERequestRangeSpecification::ALL_DATA:
		m_range_specification = ERequestRangeSpecification::ALL_DATA;
		return true;
	case ERequestRangeSpecification::RANGE_OF_DATA:
		m_range_specification = ERequestRangeSpecification::RANGE_OF_DATA;
		return true;

	default:
		return false;
	}
}

ERequestRangeSpecification IRequestExc::IsSpecial()
{
	//added to nlohman????
	//std::string specification = 
		//m_request.substr(m_request.find('\"' + "special" + '\"'));
	return ERequestRangeSpecification();
}
