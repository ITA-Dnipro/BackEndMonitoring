#pragma once
#include "stdafx.h"
#include "CAcceptor.h"
#include "DataHolder.h"
#include "CServiceConnectionHandler.h"
// This class works with server 
class CAcceptorWrapper
{
public:
	CAcceptorWrapper();
	void Start();

private:
	std::unique_ptr<CAcceptor> m_server_acceptor;
	std::unique_ptr<CServiceConnectionHandler> m_service_handler;
	std::unique_ptr<CSocketWrapper> m_stream;
};

