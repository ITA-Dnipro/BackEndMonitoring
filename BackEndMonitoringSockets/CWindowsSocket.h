#pragma once
#include <WinSock2.h>
#include <ws2tcpip.h>


namespace WindowsSocket
{
	class CWindowsSocket
	{
	public:
		CWindowsSocket();
		virtual ~CWindowsSocket();

	protected:
		bool StartLibrary();
		bool CloseLibrary();

		SOCKET m_socket;
	};
}

