#pragma once

class CRequestHandler
{
public:
	CRequestHandler() = delete;
	CRequestHandler(const std::string& request) : m_request(request)
	{ };
	CRequestHandler(const CRequestHandler&) = delete;
	CRequestHandler(CRequestHandler&&) = delete;

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
	const std::string& m_request;
	//add some ref to get path (in other word, add ref to DB (Vitalie)
};

