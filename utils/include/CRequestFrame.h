#pragma once

#include "CInteractionFrame.h"
#include "EFrameError.h"

class CRequestFrame : public CInteractionFrame
{
public:
    CRequestFrame() = default;

    [[nodiscard]] bool TryFormateRequest(std::string& var_to_save, 
        ERequestType req_typ, ERequestRangeSpecification spec_typ,
        const std::string& date_of_start = "", 
        const std::string& date_of_end = "", 
        EFrameError error = EFrameError::NONE);

private:
    nlohmann::json m_formatted_request;
};

