#include "stdafx.h"

#include "ERequestType.h"
#include "CRequestExcAllData.h"
#include "CRequestExcDiskData.h"
#include "CRequestExcProcessData.h"
#include "CDataProvider.h"
#include "GlobalVariable.h"
#include "CResponseFrame.h"
#include "EResponseError.h"

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

    if (!TryValidateRequest(request_str))
    {
        response.TryFormateResponse(answer, "",
            EResponseError::INCORRECT_REQUEST); 
        //log and return true
        return false;
    }

    switch (AnalyzeRequestType(request_str))
    {
    case ERequestType::ALL_DATA:
        if (!ExecuteRequest(answer, std::make_shared<CRequestExcAllData>(
            request_str, std::make_shared<CDataProvider>(m_data_base))))
        {
            response.TryFormateResponse(answer, "",
                EResponseError::INCORRECT_REQUEST); 
            return false;
        }
        break;
    case ERequestType::DISKS_DATA:
        if(!ExecuteRequest(answer, std::make_shared<CRequestExcDiskData>(
            request_str, std::make_shared<CDataProvider>(m_data_base))))
        {
            response.TryFormateResponse(answer, "",
                EResponseError::INCORRECT_REQUEST); 
            return false;
        }
        break;
    case ERequestType::PROCESSES_DATA:
        if(!ExecuteRequest(answer, std::make_shared<CRequestExcProcessData>(
            request_str, std::make_shared<CDataProvider>(m_data_base))))
        {
            response.TryFormateResponse(answer, "",
                EResponseError::INCORRECT_REQUEST); 
            return false;
        }
        break;
    default:
    {
        response.TryFormateResponse(answer, "", 
            EResponseError::INCORRECT_REQUEST);
        return false;
    }
    }

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
    return ERequestType(request[GlobalVariable::c_request_key_req_typ]);
}

bool CRequestHandler::ExecuteRequest(std::string& answer, 
    std::shared_ptr<IRequestExc> request_executer)
{
    return request_executer->Execute(answer);
}
