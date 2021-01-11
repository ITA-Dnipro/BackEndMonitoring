#pragma once


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
