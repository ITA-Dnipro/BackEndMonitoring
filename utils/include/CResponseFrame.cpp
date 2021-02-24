#include "stdafx.h"

#include "ERequestType.h"
#include "ERequestRangeSpecification.h"
#include "GlobalVariable.h"

#include "CResponseFrame.h"

CResponseFrame::CResponseFrame(const std::string& guid) : CInteractionFrame(guid)
{ }

CResponseFrame::CResponseFrame(const CInteractionFrame& orig) :
    CInteractionFrame(orig)
{ }

bool CResponseFrame::TryFormateResponse(std::string& response,
    const std::string& json_data,
    EFrameError error) 
{
    m_formatted_request[GlobalVariable::c_request_key_id] = m_guid;
    m_formatted_request[GlobalVariable::c_frame_error] = error;
	
    if (!json_data.empty())
    {
    m_formatted_request[GlobalVariable::c_response_data] =
        nlohmann::json::parse(json_data);
	}
    else
    {
        m_formatted_request[GlobalVariable::c_response_data] =
            nlohmann::json::parse("0");
    }
    response = m_formatted_request.dump();
	
	return !response.empty();
}
