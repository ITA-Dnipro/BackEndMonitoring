#pragma once

class CServerResponseHolder
{
public:
	void SetResponse(const std::string& response);
	std::string GetResponse() const;

private:
	std::string m_response;
};

