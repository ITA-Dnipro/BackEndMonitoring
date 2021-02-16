#include "stdafx.h"

#include "IRequestExc.h"
#include "ERequestType.h"

#include "CRequestHandler.h"

bool CRequestHandler::HandleRequest(std::string& answer)
{
    if (!TryValidateRequest())
    {
        //log
        return false;
    }

    switch (AnalyzeRequestType())
    {
    case ERequestType::ALL_DATA:
        ExecuteRequest(answer, std::make_shared<IRequestExc>(m_request));
        break;
    case ERequestType::DISKS_DATA:
        ExecuteRequest(answer, std::make_shared<IRequestExc>(m_request));
        break;
    case ERequestType::PROCESSES_DATA:
        ExecuteRequest(answer, std::make_shared<IRequestExc>(m_request));
        break;
    case ERequestType::INCORRECT_REQUEST:
        //write to log
        return false;
    default:
        //function worked incorrect. Write to log
        return false;
    }

    return true;
}

bool CRequestHandler::TryValidateRequest()
{
    //false if not valid
    return false;
}

ERequestType CRequestHandler::AnalyzeRequestType()
{
    return ERequestType();
}

bool CRequestHandler::ExecuteRequest(std::string& answer, 
    std::shared_ptr<IRequestExc> request_executer)
{
    return request_executer->Execute(answer);
}
