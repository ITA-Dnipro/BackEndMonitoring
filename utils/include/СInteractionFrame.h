#pragma once

#include "CJSONFormatter.h"

class �InteractionFrame
{
public:
	�InteractionFrame();
	�InteractionFrame(const �InteractionFrame& orig);
	�InteractionFrame(�InteractionFrame&&) noexcept = default;

protected:
	std::string m_guid;
};

