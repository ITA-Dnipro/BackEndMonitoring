#include "stdafx.h"

#include "IRequestExc.h"
#include "ERequestType.h"
#include "CRequestExcAllData.h"
#include "CRequestExcDiskData.h"
#include "CRequestExcProcessData.h"
#include "CDataProvider.h"
#include "GlobalVariable.h"

#include "CRequestHandler.h"

CRequestHandler::CRequestHandler(const std::string& request, 
    std::shared_ptr<IInfoDatabase> p_processes_data,
    std::shared_ptr<IInfoDatabase> p_disks_data,
    std::shared_ptr<IInfoDatabase> p_resources_data) :
        m_request(request), m_data_base(p_processes_data, 
            p_disks_data, p_resources_data)
{ }

bool CRequestHandler::HandleRequest(std::string& answer)
{
    if (!TryValidateRequest())
    {
        //log
        return false;
    }

    nlohmann::json request = nlohmann::json::parse(m_request);

    switch (AnalyzeRequestType(request))
    {
    case ERequestType::ALL_DATA:
        ExecuteRequest(answer, std::make_shared<CRequestExcAllData>(
            m_request, std::make_shared<CDataProvider>(m_data_base)));
        break;
    case ERequestType::DISKS_DATA:
        ExecuteRequest(answer, std::make_shared<CRequestExcDiskData>(
            m_request, std::make_shared<CDataProvider>(m_data_base)));
        break;
    case ERequestType::PROCESSES_DATA:
        ExecuteRequest(answer, std::make_shared<CRequestExcProcessData>(
            m_request, std::make_shared<CDataProvider>(m_data_base)));
        break;
    //case ERequestType::INCORRECT_REQUEST:
    //    //write to log
    //    return false;
    default:
        //function worked incorrect. Write to log
        return false;
    }

    //generate response

    return true;
}

bool CRequestHandler::TryValidateRequest()
{
    std::vector<bool> answers;
    nlohmann::json request = nlohmann::json::parse(m_request);
    for (const auto& [key, value] : request.items())
    {
        if (GlobalVariable::c_request_key_id == key)
        {
            answers.emplace_back(true);
        }
        if (GlobalVariable::c_request_key_req_typ == key)
        {
            answers.emplace_back(true);
        }
        if (GlobalVariable::c_request_key_duration == key)
        {
            answers.emplace_back(true);
        }
        if (GlobalVariable::c_request_key_spec == key)
        {
            answers.emplace_back(true);
        }
    }

    //false if not valid
    return 4 == answers.size();
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
