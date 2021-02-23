#include "stdafx.h"

#include "EFrameError.h"
#include "GlobalVariable.h"

#include "CResponseHandler.h"

CResponseHandler::CResponseHandler() : CInteractionHandler()
{ }

bool CResponseHandler::HandleResponse(const std::string& guid, 
    const std::string &response, std::string& var_storage)
{
    try
    {
        if (!TryValidate(guid, response))
        {
            return false;
        }
	    
	    m_json_temp = nlohmann::json::parse(response);
        switch (DetermineErrorInResponse(m_json_temp))
	    {
	    case EFrameError::NONE:
            m_json_temp = m_json_temp[GlobalVariable::c_response_data];
	    	break;
	    default:
            m_json_temp.clear();
	    	return false;
	    }

        var_storage = m_json_temp.dump();
    }
    catch (...)
    {
        return false;
    }

	return true;
}

EFrameError CResponseHandler::GetErrorCodeFromFrame(
    const std::string& response_str)
{
    nlohmann::json response = nlohmann::json::parse(response_str);
    int err = response[GlobalVariable::c_frame_error].get<int>();
    return EFrameError(err);
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
        if (GlobalVariable::c_frame_error == key)
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

EFrameError CResponseHandler::DetermineErrorInResponse(
	const nlohmann::json& response)
{
	return response[GlobalVariable::c_frame_error];
}
