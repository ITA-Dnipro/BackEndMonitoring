#pragma once

#include "CDataProvider.h"
#include "IRequestExc.h"

class CRequestHandler
{
public:
	CRequestHandler() = delete;
	explicit CRequestHandler(const std::string& request);
	explicit CRequestHandler(const std::string& request,
		std::shared_ptr<IInfoDatabase> p_processes_data,
		std::shared_ptr<IInfoDatabase> p_disks_data,
		std::shared_ptr<IInfoDatabase> p_resources_data);
	CRequestHandler(const CRequestHandler&) = delete;
	CRequestHandler(CRequestHandler&&) = default;

	[[nodiscard]] bool HandleRequest(std::string& answer);

private:
	//Request validator is calling here
	[[nodiscard]] bool TryValidateRequest();
	//detemine request type
	[[nodiscard]] ERequestType AnalyzeRequestType(
		const nlohmann::json& request) const;
	//get infromation that request need
	[[nodiscard]] bool ExecuteRequest(std::string& answer, 
		std::shared_ptr<IRequestExc> request_executer);

private:
	CDataProvider m_data_base;
	const std::string& m_request;
};

