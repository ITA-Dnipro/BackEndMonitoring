 #pragma once
#include <string>
#include "CBaseSocket.h"

namespace SocketWrapper
{
	class CSocketWrapper : public BaseSocket::CBaseSocket
	{
	public:
		CSocketWrapper();
		CSocketWrapper(const int socket);
		~CSocketWrapper();
		void SetSocket(const int socket);
		int GetHandle() const;
		std::string Receive(const int client_socket);
		bool Send(const int client_socket, const std::string& line);

	};
}
