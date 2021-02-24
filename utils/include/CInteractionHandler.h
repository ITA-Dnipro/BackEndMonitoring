#pragma once

#include "EFrameError.h"

class CInteractionHandler
{
public:
	CInteractionHandler() = default;
	CInteractionHandler(const CInteractionHandler&) = delete;
	CInteractionHandler(CInteractionHandler&&) noexcept = delete;

	[[nodiscard]] virtual EFrameError GetErrorCodeFromFrame(
		const std::string& response) = 0;

protected:
	size_t m_num_of_pairs_in_json;
};

