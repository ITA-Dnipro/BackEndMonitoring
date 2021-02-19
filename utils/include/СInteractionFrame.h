#pragma once

#include "CJSONFormatter.h"

class ÑInteractionFrame
{
public:
	ÑInteractionFrame();
	ÑInteractionFrame(const ÑInteractionFrame& orig);
	ÑInteractionFrame(ÑInteractionFrame&&) noexcept = default;

protected:
	std::string m_guid;
};

