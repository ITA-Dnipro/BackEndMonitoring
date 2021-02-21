#pragma once

#include "CJSONFormatter.h"

class CInteractionFrame
{
public:
	CInteractionFrame();
	CInteractionFrame(const std::string& guid);
	CInteractionFrame(const CInteractionFrame& orig);
	CInteractionFrame(CInteractionFrame&&) noexcept = default;

protected:
	std::string m_guid;
};

