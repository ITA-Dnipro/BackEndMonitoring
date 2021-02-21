#include "stdafx.h"

#include "CInteractionFrame.h"

CInteractionFrame::CInteractionFrame(const std::string & guid) : m_guid(guid)
{ }

CInteractionFrame::CInteractionFrame(const CInteractionFrame & orig) : 
	m_guid(orig.m_guid)
{ }
