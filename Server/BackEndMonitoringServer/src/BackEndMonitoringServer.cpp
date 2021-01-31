#include "stdafx.h"

#include "CService.h"
#include "CCommandLineHandler.h"
#include "CServiceHandler.h"
#include "Utils.h"
#include "CHardwareStatusSpecification.h"
#include "CLogicalDiskInfoMonitoring.h"


int main(int argc, char** argv)
{
    CEvent stop;
    CThreadSafeVariable<CJSONFormatterLogicalDisk> jsonf;
    CHardwareStatusSpecification specification_from_xml(
        std::chrono::duration<int>(1), "info.json",
        EMemoryConvertType::GIGABYTES);
    CLogicalDiskInfoMonitoring logical_disks(stop, &specification_from_xml, jsonf);
    logical_disks.StartMonitoringInfo();
    
    return 0;
}


// FOR TESTING
//#include "stdafx.h"
//#include "../BackEndMonitoring/Sockets/BackEndMonitoringSockets/include/CAcceptorWrapper.h"
//#include "CThreadPool.h"
//#include "CLogger/include/Log.h"
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
//	std::shared_ptr<CThreadPool>m_thread_pool =
//		std::make_shared<CThreadPool>(num_threads, m_stop_event);
//	std::unique_ptr<CAcceptorWrapper>m_acceptor_socket =
//		std::make_unique<CAcceptorWrapper>(port, ip_address,
//			m_stop_event, m_thread_pool, false, 5);
//
//	m_acceptor_socket->StartServer();
//	system("pause");
//
//	CLOG_DESTROY();
//
//	return 0;
//}