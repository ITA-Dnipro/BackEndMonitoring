#include "stdafx.h"

#include "EResponseError.h"
#include "GlobalVariable.h"

#include "CResponseHandler.h"

CResponseHandler::CResponseHandler() : CInteractionHandler()
{ }

bool CResponseHandler::HandleResponse(const std::string& guid, 
    const std::string &response, std::string& var_storage)
{
    if (!TryValidate(guid, response))
    {
        return false;
    }
	
	m_json_temp = nlohmann::json::parse(response);
    switch (DetermineErrorInResponse(m_json_temp))
	{
	case EResponseError::NONE:
        m_json_temp = m_json_temp[GlobalVariable::c_response_data];
		break;
	case EResponseError::INCORRECT_REQUEST:
		// log
        m_json_temp.clear();
		return false;
	default:
		// log
		return false;
	}

    var_storage = m_json_temp.dump();

	return true;
}

bool CResponseHandler::TryValidate(const std::string& guid, 
    const std::string& response_str)
{
    std::vector<bool> answer;
    nlohmann::json response = nlohmann::json::parse(response_str);
    
    for (const auto& [key, value] : response.items())
    {
        if (GlobalVariable::c_request_key_id == key)
        {
            answer.emplace_back(true);
            continue;
        }
        if (GlobalVariable::c_response_data == key)
        {
            answer.emplace_back(true);
            continue;
        }
        if (GlobalVariable::c_response_error == key)
        {
            answer.emplace_back(true);
            continue;
        }
    }
    if (guid == response[GlobalVariable::c_request_key_id])
    {
        answer.emplace_back(true);
    }

    return 4 == answer.size();
}

EResponseError CResponseHandler::DetermineErrorInResponse(
	const nlohmann::json& response)
{
	return response[GlobalVariable::c_response_error];
}
