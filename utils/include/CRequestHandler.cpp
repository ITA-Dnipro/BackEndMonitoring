#include "stdafx.h"

#include "ERequestType.h"
#include "CRequestExcAllData.h"
#include "CRequestExcDiskData.h"
#include "CRequestExcProcessData.h"
#include "CDataProvider.h"
#include "GlobalVariable.h"
#include "CResponseFrame.h"
#include "EFrameError.h"
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
    nlohmann::json request;
	try
	{
        request = nlohmann::json::parse(request_str);
		
	}
	catch(...)
	{
        CLOG_ERROR("Incorrect request!!!");
        return false;
	}
    CResponseFrame response(request[GlobalVariable::c_request_key_id]);
    CLOG_DEBUG_START_FUNCTION();
    try
    {

        if (!TryValidateRequest(request_str))
        {
            response.TryFormateResponse(answer, "",
                EFrameError::INCORRECT_REQUEST); 
            //log and return true
	    	CLOG_ERROR("Invalid request from the client!!!");
            return false;
        }
        EFrameError error_from_frame = GetErrorCodeFromFrame(request_str);
        if (EFrameError::NONE != error_from_frame)
        {
            response.TryFormateResponse(answer, "",
                error_from_frame);
            //log and return true
            CLOG_ERROR("Invalid request from the client!!!");
            return false;
        }
        ERequestType req_typ = AnalyzeRequestType(request);

        std::shared_ptr<IRequestExc> request_hahdler;

        switch (req_typ)
        {
        case ERequestType::ALL_DATA:
            request_hahdler = std::make_shared<CRequestExcAllData>(
                request_str, std::make_shared<CDataProvider>(m_data_base));
            CLOG_DEBUG("All data request from the client");
            break;
        case ERequestType::DISKS_DATA:
            request_hahdler = std::make_shared<CRequestExcDiskData>(
                request_str, std::make_shared<CDataProvider>(m_data_base));
            CLOG_DEBUG("Disks data request from the client");
            break;
        case ERequestType::PROCESSES_DATA:
            request_hahdler = std::make_shared<CRequestExcProcessData>(
                request_str, std::make_shared<CDataProvider>(m_data_base));
            CLOG_DEBUG("Processes data request from the client");
            break;
        default:
        {
            response.TryFormateResponse(answer, "", 
                EFrameError::LOST_REQUEST);
            CLOG_ERROR("Default case, incorrect error");
            return false;
        }
        }
        if (!ExecuteRequest(answer, request_hahdler))
        {
            response.TryFormateResponse(answer, "",
                EFrameError::INCORRECT_REQUEST);
        }

    }
    catch (...)
    {
        return response.TryFormateResponse(answer, answer, 
            EFrameError::INCORRECT_REQUEST);
    }
    CLOG_DEBUG_END_FUNCTION();

    return response.TryFormateResponse(answer, answer, EFrameError::NONE);
}

EFrameError CRequestHandler::GetErrorCodeFromFrame(
    const std::string& request_str)
{
    nlohmann::json request = nlohmann::json::parse(request_str);
    int err = request[GlobalVariable::c_frame_error].get<int>();
    return EFrameError(err);
}

bool CRequestHandler::TryValidateRequest(const std::string& request_str)
{
    std::vector<bool> answer;
        nlohmann::json request = nlohmann::json::parse(request_str);

        m_num_of_pairs_in_json = 0;
    for (const auto& [key, value] : request.items())
    {
        ++m_num_of_pairs_in_json;
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
    return (GlobalVariable::max_num_of_pair_in_request >= 
        m_num_of_pairs_in_json) && (3 == answer.size());
}

ERequestType CRequestHandler::AnalyzeRequestType(const nlohmann::json& request) 
const
{	
    return ERequestType(
        request[GlobalVariable::c_request_key_req_typ].get<int>());
}

bool CRequestHandler::ExecuteRequest(std::string& answer, 
    std::shared_ptr<IRequestExc> request_executer)
{
    return request_executer->Execute(answer);
}
