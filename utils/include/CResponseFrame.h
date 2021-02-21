#pragma once

#include "CInteractionFrame.h"
#include "EResponseError.h"

class CResponseFrame : public CInteractionFrame
{
public:
    CResponseFrame() = delete;
    CResponseFrame(const std::string& guid);
    CResponseFrame(const CInteractionFrame& orig);

    bool TryFormateResponse(std::string& var_to_responsesave,
        const std::string& json_data, EResponseError error);

private:
    nlohmann::json m_formatted_request;
};

