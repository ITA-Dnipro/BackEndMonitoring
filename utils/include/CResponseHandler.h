#pragma once
#include "CInteractionHandler.h"
#include "EResponseError.h"

class CResponseHandler : public CInteractionHandler
{
public:
	CResponseHandler();
	CResponseHandler(const CResponseHandler&) = delete;
	CResponseHandler(CResponseHandler&&) = delete;

	[[nodiscard]] bool HandleResponse(const std::string& guid, const std::string& response,
		nlohmann::json& json_storage);

private:
	[[nodiscard]] bool TryValidate(const std::string& guid, const std::string& response);
	[[nodiscard]] EResponseError DetermineErrorInResponse(
		const nlohmann::json& response);
};

