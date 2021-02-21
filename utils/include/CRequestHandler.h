#pragma once

#include "CDataProvider.h"
#include "IRequestExc.h"
#include "CInteractionHandler.h"
#include "ERequestType.h"

class CRequestHandler : public  CInteractionHandler
{
public:
	CRequestHandler() = delete;
	explicit CRequestHandler(
		std::shared_ptr<IInfoDatabase> p_processes_data,
		std::shared_ptr<IInfoDatabase> p_disks_data,
		std::shared_ptr<IInfoDatabase> p_resources_data);
	CRequestHandler(const CRequestHandler&);
	CRequestHandler(CRequestHandler&&) = default;

	[[nodiscard]] bool HandleRequest(const std::string& m_request, 
		std::string& answer);

private:
	//Request validator is calling here
	[[nodiscard]] bool TryValidateRequest(const std::string& m_request);
	//detemine request type
	[[nodiscard]] ERequestType AnalyzeRequestType(
		const nlohmann::json& request) const;
	//get infromation that request need
	[[nodiscard]] bool ExecuteRequest(std::string& answer, 
		std::shared_ptr<IRequestExc> request_executer);

private:
	CDataProvider m_data_base;
};

