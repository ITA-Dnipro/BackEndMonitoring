#pragma once

#include "CInteractionHandler.h"

enum class EFrameError;

class CResponseHandler : public CInteractionHandler
{
public:
	CResponseHandler();
	CResponseHandler(const CResponseHandler&) = delete;
	CResponseHandler(CResponseHandler&&) = delete;

	[[nodiscard]] bool HandleResponse(const std::string& guid, 
		const std::string& response, std::string& var_storage);

	[[nodiscard]] virtual EFrameError GetErrorCodeFromFrame(
		const std::string& response) override;

private:
	[[nodiscard]] bool TryValidate(const std::string& guid, 
		const std::string& response);
	[[nodiscard]] EFrameError DetermineErrorInResponse(
		const nlohmann::json& response);

private:
	nlohmann::json m_json_temp;
};

