#include "stdafx.h"
#include "CConnectorWrapper.h"

CConnectorWrapper::CConnectorWrapper()
{
	m_dispatcher = CInitiationDispatcher::GetInstance();
	m_connector = std::make_unique<CConnector>(1111,
		"127.0.0.1", m_dispatcher);
	m_stream.SetSocket(m_connector->GetHandle());
	std::cout << m_dispatcher << " CInitiationDispatcher address"
		<< std::endl;
}

CConnectorWrapper::~CConnectorWrapper()
{
	delete m_dispatcher;
	delete m_handler;
}

void CConnectorWrapper::MakeRequest(const std::string& message)
{
	m_handler = new CClientConnectionHandler(EventType::WRITE_EVENT,
		m_stream, m_dispatcher);
	m_dispatcher->RegisterHandler(m_handler,
		EventType::WRITE_EVENT);
	Connect();
}

std::string CConnectorWrapper::GetResponse()
{
	return m_stream.Receive(m_handler->GetHandle());
}

void CConnectorWrapper::Connect()
{
	m_connector->Connect(m_handler);
}
