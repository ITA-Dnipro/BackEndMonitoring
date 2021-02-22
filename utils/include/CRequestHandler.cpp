#include "stdafx.h"

#include "ERequestType.h"
#include "CRequestExcAllData.h"
#include "CRequestExcDiskData.h"
#include "CRequestExcProcessData.h"
#include "CDataProvider.h"
#include "GlobalVariable.h"
#include "CResponseFrame.h"
#include "EResponseError.h"
#include "Log.h"
#include "CRequestHandler.h"

CRequestHandler::CRequestHandler(
    std::shared_ptr<IInfoDatabase> p_processes_data,
    std::shared_ptr<IInfoDatabase> p_disks_data,
    std::shared_ptr<IInfoDatabase> p_resources_data) : CInteractionHandler(),
         m_data_base(p_processes_data, p_disks_data, p_resources_data)
{ }

CRequestHandler::CRequestHandler(const CRequestHandler& orig) : 
    m_data_base(orig.m_data_base)
{
}

bool CRequestHandler::HandleRequest(const std::string& request_str, 
    std::string& answer)
{
    nlohmann::json request = nlohmann::json::parse(request_str);
    CResponseFrame response(request[GlobalVariable::c_request_key_id]);
    CLOG_DEBUG_START_FUNCTION();

    if (!TryValidateRequest(request_str))
    {
        response.TryFormateResponse(answer, "",
            EResponseError::INCORRECT_REQUEST); 
        //log and return true
		CLOG_ERROR("Invalid request from the client!!!");
        return false;
    }
    switch (AnalyzeRequestType(request))
    {
    case ERequestType::ALL_DATA:
        if (!ExecuteRequest(answer, std::make_shared<CRequestExcAllData>(
            request_str, std::make_shared<CDataProvider>(m_data_base))))
        {
            response.TryFormateResponse(answer, "",
                EResponseError::INCORRECT_REQUEST); 
            return false;
        }
        CLOG_DEBUG("All data request from the client");

        break;
    case ERequestType::DISKS_DATA:
        if(!ExecuteRequest(answer, std::make_shared<CRequestExcDiskData>(
            request_str, std::make_shared<CDataProvider>(m_data_base))))
        {
            response.TryFormateResponse(answer, "",
                EResponseError::INCORRECT_REQUEST); 
            return false;
        }
        CLOG_DEBUG("Disks data request from the client");

        break;
    case ERequestType::PROCESSES_DATA:
        if(!ExecuteRequest(answer, std::make_shared<CRequestExcProcessData>(
            request_str, std::make_shared<CDataProvider>(m_data_base))))
        {
            response.TryFormateResponse(answer, "",
                EResponseError::INCORRECT_REQUEST); 
            return false;
        }
        CLOG_DEBUG("Processes data request from the client");

        break;
    default:
    {
        response.TryFormateResponse(answer, "", 
            EResponseError::INCORRECT_REQUEST);
        CLOG_ERROR("Default case, incorrect error");
        return false;
    }
    }
    CLOG_DEBUG_END_FUNCTION();
    // could be a problem
    return response.TryFormateResponse(answer, answer, EResponseError::NONE);
}

bool CRequestHandler::TryValidateRequest(const std::string& request_str)
{
    std::vector<bool> answer;
        nlohmann::json request = nlohmann::json::parse(request_str);
    for (const auto& [key, value] : request.items())
    {
        if (GlobalVariable::c_request_key_id == key)
        {
            answer.emplace_back(true);
            continue;
        }
        if (GlobalVariable::c_request_key_req_typ == key)
        {
            answer.emplace_back(true);
            continue;
        }
        if (GlobalVariable::c_request_key_spec == key)
        {
            answer.emplace_back(true);
            continue;
        }
    }

    //false if not valid
    return 3 == answer.size();
}

ERequestType CRequestHandler::AnalyzeRequestType(const nlohmann::json& request) 
const
{
    int req_code = request[GlobalVariable::c_request_key_req_typ].get<int>();
	
    return ERequestType(req_code);
}

bool CRequestHandler::ExecuteRequest(std::string& answer, 
    std::shared_ptr<IRequestExc> request_executer)
{
    return request_executer->Execute(answer);
}
