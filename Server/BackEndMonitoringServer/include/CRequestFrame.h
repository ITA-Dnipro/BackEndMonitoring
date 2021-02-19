#pragma once

#include "ÑInteractionFrame.h"

class CRequestFrame :
    public ÑInteractionFrame
{
public:
    CRequestFrame() = default;

    [[nodiscard]] bool TryFormateRequest(std::string& var_to_save, 
        ERequestType req_typ, ERequestRangeSpecification spec_typ,
        const std::string& date_of_start = "", const std::string& date_of_end = "");

private:
    nlohmann::json m_formatted_request;
};

