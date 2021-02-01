
#include "stdafx.h"

#include "CService.h"
#include "CCommandLineHandler.h"
#include "CServiceHandler.h"
#include "Utils.h"


int main(int argc, char** argv)
{
    auto parser = std::make_unique<CommandLineHandler>();

    bool success = parser->Parse(argc, argv);

    if (!success)
    {
        Utils::DisplayMessage("Invalid parameters");
        return EXIT_FAILURE;
    }

    const int return_code = success ? 0 : 1;

    return return_code;

    return 0;
};



////// FOR TESTING
////#include "stdafx.h"
//
//#include "../BackEndMonitoring/Sockets/BackEndMonitoringSockets/include/CAcceptorWrapper.h"
//#include "Clogger/include/Log.h"
//#include "CEvent.h"
//#include "CThreadPool.h"
//#include "EMemoryConvertType.h"
//#include "CProcessInfo.h"
//#include "CJSONFormatterProcess.h"
//#include "CJSONFormatterLogicalDisk.h"
//#include "CHardwareStatusSpecification.h"
//#include "CContainerOfProcesses.h"
//#include "CContainerOfLogicalDisk.h"
//#include "CProcessesInfoMonitoring.h"
//#include "CLogicalDiskInfoMonitoring.h"
//#include "Sockets/BackEndMonitoringSockets/include/CDataReceiver.h"
//
//int main()
//{
//	std::fstream stream("Log.txt", std::ios_base::out);
//
//	CLOG_START_CREATION();
//
//	CLOG_SET_LOG_NAME("Logger");
//	CLOG_SET_LOG_LEVEL(ELogLevel::DEBUG_LEVEL);
//	CLOG_SET_LOG_CONFIG(ELogConfig::LOG_NAME, ELogConfig::LOG_LEVEL,
//		ELogConfig::CALL_TIME, ELogConfig::THREAD_ID, ELogConfig::FILE_NAME,
//		ELogConfig::FUNCTION_NAME, ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE,
//		ELogConfig::PARAMS);
//
//	CLOG_ADD_SAFE_STREAM(stream);
//
//	CLOG_BUILD();
//
//	CLOG_END_CREATION();
//
//	CEvent event;
//	size_t num_threads = 3;
//	int port = 1111;
//	std::string ip_address = "127.0.0.1";
//	CEvent m_stop_event;
//
//	auto m_disks_monitor = std::make_unique<CLogicalDiskInfoMonitoring>(m_stop_event,
//		specification,
//		m_disks_json);
//
//	auto m_processes_monitor = std::make_unique<CProcessesInfoMonitoring>(
//		tick, path_to_file, measure_in, m_stop_event, m_processes_json);
//
//	CDataReceiver json_data(m_processes_json, m_disks_json);
//
//	std::shared_ptr<CThreadPool>m_thread_pool =
//		std::make_shared<CThreadPool>(num_threads, m_stop_event);
//	std::unique_ptr<CAcceptorWrapper>m_acceptor_socket =
//		std::make_unique<CAcceptorWrapper>(port, ip_address,
//			m_stop_event, m_thread_pool, false, 5, nullptr);
//
//	m_acceptor_socket->StartServer();
//	system("pause");
//
//	CLOG_DESTROY();
//
//	return 0;
//}