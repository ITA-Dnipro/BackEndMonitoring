#include "stdafx.h"

#include "CEvent.h"
#include "CThreadPool.h"
#include "EMemoryConvertType.h"
#include "CProcessInfo.h"
#include "CJSONFormatterProcess.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CHardwareStatusSpecification.h"
#include "CContainerOfProcesses.h"
#include "CContainerOfLogicalDisk.h"
#include "CProcessesInfoMonitoring.h"
#include "CLogicalDiskInfoMonitoring.h"
#include "Sockets/BackEndMonitoringSockets/include/CDataProvider.h"
#include "Utils.h"
#include "CXMLDataReader.h"
#include "CLoggingSettings.h"
#include "CThreadPoolSettings.h"
#include "CHDDInfoSettings.h"
#include "CProcessesInfoSettings.h"
#include "CServerSettings.h"
#include "CTimeSettings.h"
#include "CRequestHandler.h"

#include "CService.h"

void CService::RunServer()
{
    //Sleep(20000);
    std::string path_to_log_file(Utils::GetRelativePath() + "Log.txt");
    ELogLevel log_level = ELogLevel::DEBUG_LEVEL;
    if (!InitializeLogger(path_to_log_file, log_level))
    {
        return;
    }
    CLOG_DEBUG_START_FUNCTION();

    auto xml_reader = std::make_shared<CXMLDataReader>();
    CLOG_TRACE_VAR_CREATION(xml_reader);

    xml_reader->Initialize(Utils::GetRelativePath() + "config.xml");

    CLoggingSettings log_sett(xml_reader);
    CLOG_TRACE_VAR_CREATION(log_sett);
    log_sett.ReadConfigurationFromFile();

    CThreadPoolSettings thred_pool_sett(xml_reader);
    CLOG_TRACE_VAR_CREATION(thred_pool_sett);
    thred_pool_sett.ReadConfigurationFromFile();

    if(!InitializeThreadPool(thred_pool_sett))
    {
        CLOG_PROD("ERROR! Can't initialize thread pool!");
        return;
    }

    CProcessesInfoSettings process_sett(xml_reader);
    process_sett.ReadConfigurationFromFile();
    if (process_sett.GetCheckProcesses())
    {
        if (InitializeProcessesMonitoring(process_sett))
        {
            m_p_thread_pool->Enqueue([this]()
            {
                m_processes_monitor->StartMonitoringInfo();
            });
        }
        else
        {
            CLOG_PROD("ERROR! Can't initialize processes monitoring!");
            return;
        }
    }

    CHDDInfoSettings hdd_sett(xml_reader);
    hdd_sett.ReadConfigurationFromFile();
    if (hdd_sett.GetCheckHdd())
    {
        if (InitializeLogicalDiscMonitoring(hdd_sett))
        {
            m_p_thread_pool->Enqueue([this]()
            {
                m_disks_monitor->StartMonitoringInfo();
            });
        }
        else
        {
            CLOG_PROD("ERROR! Can't initialize logical disks monitoring!");
            return;
        }
    }

    CServerSettings server_sett(xml_reader);
    CLOG_TRACE_VAR_CREATION(server_sett);
    server_sett.ReadConfigurationFromFile();

    if (!InitializeSockets(server_sett))
    {
        CLOG_PROD("ERROR! Can't create sockets!");
        return;
    }
    CRequestHandler request_handler(m_p_processes_data, m_p_drives_data,
                            m_p_resources_data);
    CLOG_TRACE_VAR_CREATION(request_handler);

    if (!m_p_acceptor_socket->Initialize(std::move(m_p_thread_pool),
        request_handler, SOMAXCONN))
    {
        CLOG_PROD("ERROR! Can't initialize sockets!");
        return;
    }

    m_p_acceptor_socket->Execute( );
    CLOG_DEBUG_END_FUNCTION();
}

bool CService::InitializeLogger(
    const std::string& path_to_log_file,
    ELogLevel level)
{
    CLOG_DEBUG_START_FUNCTION();
    m_log_stream = std::make_unique<std::fstream>(
        path_to_log_file,
        std::ios_base::app);

    if (m_log_stream->is_open())
    {
        CLOG_CREATION_START( );

        CLOG_CREATION_SET_LOG_NAME("Logger");
        CLOG_CREATION_SET_LOG_LEVEL(level);
        CLOG_CREATION_SET_LOG_CONFIG(
            ELogConfig::LOG_NAME,
            ELogConfig::LOG_LEVEL,
            ELogConfig::CALL_TIME,
            ELogConfig::THREAD_ID,
            ELogConfig::FILE_NAME,
            ELogConfig::FUNCTION_NAME,
            ELogConfig::LINE_NUMBER,
            ELogConfig::MESSAGE,
            ELogConfig::PARAMS);

        CLOG_CREATION_ADD_SAFE_STREAM(*m_log_stream);

        CLOG_BUILD( );

        CLOG_CREATION_END( );
        return true;
    }
    CLOG_DEBUG_END_FUNCTION();
    return false;
}

bool CService::InitializeThreadPool(
    const CThreadPoolSettings& thread_pool_sett)
{
    CLOG_DEBUG_START_FUNCTION( );
    m_p_thread_pool = std::make_shared<CThreadPool>(
        thread_pool_sett.GetMaxWorkingThreads( ),
        m_stop_event);

    CLOG_TRACE_VAR_CREATION(m_p_thread_pool);
    CLOG_DEBUG_END_FUNCTION( );
    return true;
}

bool CService::InitializeLogicalDiscMonitoring(
    const CHDDInfoSettings& xml_settings)
{
    CLOG_DEBUG_START_FUNCTION( );
    CHardwareStatusSpecification* specification = new
        CHardwareStatusSpecification(
        std::chrono::seconds(xml_settings.GetPeriodTime( )),
        Utils::DefineCountType(xml_settings.GetCountType( )));

    m_p_drives_data = std::make_shared<CDrivesInfoJSONDatabase>(
        xml_settings.GetFileName( ));


    CLOG_TRACE_VAR_CREATION(specification);
    m_disks_monitor = std::make_unique<CLogicalDiskInfoMonitoring>(
        m_stop_event,
        specification,
        m_p_drives_data);

    CLOG_TRACE_VAR_CREATION(m_disks_monitor);
    CLOG_DEBUG_END_FUNCTION( );

    return true;
}

bool CService::InitializeProcessesMonitoring(
    const CProcessesInfoSettings& xml_settings)
{
    m_p_processes_data = std::make_shared<CProcessesInfoJSONDatabase>(
        xml_settings.GetFileName( ));
    m_p_resources_data = std::make_shared<CResourcesInfoJSONDatabase>();

    m_processes_monitor = std::make_unique<CProcessesInfoMonitoring>(
        std::chrono::seconds(xml_settings.GetPeriodTime()),
        Utils::DefineCountType(xml_settings.GetCountType()),
        m_stop_event,
        m_p_processes_data,
        m_p_resources_data);

    CLOG_DEBUG_START_FUNCTION( );
    CLOG_TRACE_VAR_CREATION(m_processes_monitor);
    CLOG_DEBUG_END_FUNCTION( );
    return m_processes_monitor->Initialize( );
}

bool CService::InitializeSockets(const CServerSettings& server_sett)
{
    CLOG_DEBUG_START_FUNCTION( );
    m_p_acceptor_socket = std::make_unique<CServiceHost>(
        server_sett.GetListenerPort(),
        server_sett.GetServerIpAddress(),
        server_sett.GetBlocking(),
        server_sett.GetSocketTimeout(),
        m_stop_event);

    CLOG_TRACE_VAR_CREATION(m_p_acceptor_socket);

    CLOG_DEBUG_END_FUNCTION( );
    return true;
}
