#pragma once
#include "stdafx.h"
#include "CAcceptor.h"
#include "CInitiationDispatcher.h"
// This class works with server 
class CAcceptorWrapper
{
public:
	CAcceptorWrapper();
	~CAcceptorWrapper();
	void Start();

private:
	CAcceptor* m_server_acceptor;
	CInitiationDispatcher* m_dispatcher;

};

