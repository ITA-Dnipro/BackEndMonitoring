 #pragma once
#include "stdafx.h"
#include "CBaseSocket.h"

//This class allows to send and receive data from one side to another
class CSocketWrapper : CBaseSocket
{
public:
	CSocketWrapper();
	CSocketWrapper(const int socket);
	virtual ~CSocketWrapper();
	void SetSocket(const int socket);
	int GetHandle() const;
	std::string Receive(const int client_socket);
	bool Send(const int client_socket, const std::string& line);

};