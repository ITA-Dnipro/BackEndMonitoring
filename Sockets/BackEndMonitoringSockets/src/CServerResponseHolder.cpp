#include "stdafx.h"
#include "CServerResponseHolder.h"

void CServerResponseHolder::SetResponse(const std::string& response)
{
	m_response = response;
}

std::string CServerResponseHolder::GetResponse() const
{
	return m_response;
}
