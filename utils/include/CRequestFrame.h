#pragma once

#include "CInteractionFrame.h"
#include "EFrameError.h"
#include "ERequestType.h"
#include "ERequestRangeSpecification.h"

class CRequestFrame : public CInteractionFrame
{
public:
    CRequestFrame() = default;

		bool TryFormateRequest(std::string& var_to_save, 
        ERequestType req_typ,
        EFrameError error = EFrameError::NONE,
        ERequestRangeSpecification spec_typ = ERequestRangeSpecification::LAST_DATA,
        const std::string& date_of_start = "", 
        const std::string& date_of_end = "");

private:
    nlohmann::json m_formatted_request;
};

