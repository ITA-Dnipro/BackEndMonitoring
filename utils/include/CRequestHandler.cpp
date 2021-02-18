#include "stdafx.h"

#include "IRequestExc.h"
#include "ERequestType.h"

#include "CRequestHandler.h"

#define id_ "id"
#define req_typ_ "req_typ"
#define spec_ "spec"
#define dur_ "dur"


bool CRequestHandler::HandleRequest(std::string& answer)
{
    // todo: should I validate request with 3-rd party lib stuff or with regex?
    if (!TryValidateRequest())
    {
        //log
        return false;
    }

    nlohmann::json request = nlohmann::json::parse(m_request);

    switch (AnalyzeRequestType(request))
    {
    case ERequestType::ALL_DATA:
        //ExecuteRequest(answer, std::make_shared<CRequestExcAllData>(m_request));
        break;
    case ERequestType::DISKS_DATA:
        //ExecuteRequest(answer, std::make_shared<IRequestExc>(m_request));
        break;
    case ERequestType::PROCESSES_DATA:
        //ExecuteRequest(answer, std::make_shared<IRequestExc>(m_request));
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
        if (id_ == key)
        {
            answers.emplace_back(true);
        }
        if (req_typ_ == key)
        {
            answers.emplace_back(true);
        }
        if (dur_ == key)
        {
            answers.emplace_back(true);
        }
        if (spec_ == key)
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
    // todo: i could check is req correct here, or just let incorrect req_typ 
    // return and go to default. If second var, it'll be faster and same protected
    // but duties a little wrong
    return ERequestType(request[req_typ_]);
}

bool CRequestHandler::ExecuteRequest(std::string& answer, 
    std::shared_ptr<IRequestExc> request_executer)
{
    return request_executer->Execute(answer);
}
