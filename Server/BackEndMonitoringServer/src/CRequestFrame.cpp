#include "stdafx.h"

#include "ERequestType.h"
#include "ERequestRangeSpecification.h"
#include "GlobalVariable.h"
#include "crossguid/guid.hpp"

#include "CRequestFrame.h"


bool CRequestFrame::TryFormateRequest(std::string& var_to_save, 
	ERequestType req_typ, ERequestRangeSpecification spec_typ, 
	const std::string& date_of_start, const std::string& date_of_end)
{
	//m_guid = xg::newGuid().str();
	//var 1
	/m_guid = std::to_string(rand());
	m_formatted_request[GlobalVariable::c_request_key_id] = m_guid;
	m_formatted_request[GlobalVariable::c_request_key_req_typ] = req_typ;
	if (spec_typ == ERequestRangeSpecification::RANGE_OF_DATA && 
		(date_of_start.size() > 0 && date_of_end.size() > 0))
	{
		m_formatted_request[GlobalVariable::c_request_key_duration] = 
			{ date_of_start, date_of_end };
	}
	m_formatted_request[GlobalVariable::c_request_key_spec] = spec_typ;

	var_to_save = m_formatted_request.dump();
	return false;
}
