#pragma once
#include "stdafx.h"

// This class works with server 
class CAcceptorWrapper
{
public:
	CAcceptorWrapper();
	void Start();

private:
	CAcceptor* m_server_acceptor;
	CInitiationDispatcher* m_dispatcher;

};

