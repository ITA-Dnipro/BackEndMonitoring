//#include "stdafx.h"
//
//#include "CService.h"
//#include "CCommandLineHandler.h"
//#include "CServiceHandler.h"
//#include "Utils.h"
//
//int main(int argc, char** argv)
//{
//    auto parser = std::make_unique<CommandLineHandler>();
//
//    bool success = parser->Parse(argc, argv);
//
//    if (!success)
//    {
//        Utils::DisplayMessage("Invalid parameters");
//        return EXIT_FAILURE;
//    }
//
//    const int return_code = success ? 0 : 1;
//
//    return return_code;
//}


// FOR TESTING
#include "stdafx.h"
#include "../BackEndMonitoring/Sockets/BackEndMonitoringSockets/include/CAcceptorWrapper.h"
#include "CThreadPool.h"
#include "CThreadSafeVariable.h"

int main()
{
	CEvent event;
	size_t num_threads = 3;
	int port = 1111;
	std::string ip_address = "127.0.0.1";
	CEvent m_stop_event;
	std::shared_ptr<CThreadPool>m_thread_pool = std::make_shared<CThreadPool>(num_threads, m_stop_event);
	std::unique_ptr<CAcceptorWrapper>m_acceptor_socket = std::make_unique<CAcceptorWrapper>(port, ip_address,
		m_stop_event, m_thread_pool, false, 5);

	m_acceptor_socket->StartServer();
	system("pause");
	return 0;
}