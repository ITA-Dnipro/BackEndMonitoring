#include "CConnectorWrapper.h"

namespace ConnectorWrapper
{
	CConnectorWrapper::CConnectorWrapper()
	{
		m_dispatcher = CDispatcher::GetInstance();
		m_connector = std::make_unique<Connector::CConnector>(27015, 
			"127.0.0.1", m_dispatcher);
		m_stream.SetSocket(m_connector.get()->GetHandle());
		std::cout << m_dispatcher << std::endl;
	}

	void CConnectorWrapper::MakeRequest(const std::string& message)
	{
		m_handler = new ClientHandler(EventHandler::EventType::WRITE_EVENT, 
			m_stream, m_dispatcher);
		m_dispatcher->RegisterHandler(m_handler, 
			EventHandler::EventType::WRITE_EVENT);
		Connect();
	}

	std::string CConnectorWrapper::GetResponse()
	{
		return m_stream.Receive(m_handler->GetHandle());
	}

	void CConnectorWrapper::Connect()
	{
		m_connector.get()->Connect(m_handler);
	}

}
