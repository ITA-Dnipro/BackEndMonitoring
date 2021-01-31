#include "stdafx.h"

#include "Clogger/include/Log.h"
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
#include "Sockets/BackEndMonitoringSockets/include/CDataReceiver.h"

#include "CService.h"

// We need this to test the service
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

void CService::RunServer()
{
    //TODO Add XML Configuration interaction
    Sleep(10000);

    //Need absolute path here!!!
    std::string path_to_log_file("F:\\Git\\Log.txt");
    ELogLevel log_level = ELogLevel::DEBUG_LEVEL;
    if(!InitializeLogger(path_to_log_file, log_level))
    { return;}

    size_t num_threads = 5;
    if(!InitializeThreadPool(num_threads))
    { 
        CLOG_PROD("ERROR! Can't initialize thread pool!");
        return;
    }

    std::chrono::duration<int> tick = std::chrono::seconds(30);
    std::string path_to_disk_file("F:\\Git\\disk.json");
    std::string path_to_proc_file("F:\\Git\\proc.json");
    EMemoryConvertType measure_in = EMemoryConvertType::MEGABYTES;

    if (InitializeLogicalDiscMonitoring(tick, path_to_disk_file, measure_in))
    {
        m_p_thread_pool->Enqueue([this] ( )
                                 {
                                     m_disks_monitor->StartMonitoringInfo( );
                                 });


    }
    else
    {
        CLOG_PROD("ERROR! Can't initialize logical disks monitoring!");
        return;
    }

    if (InitializeProcessesMonitoring(tick, path_to_proc_file, measure_in))
    {
        m_p_thread_pool->Enqueue([this] ( )
                                 {
                                     m_processes_monitor->StartMonitoringInfo( );
                                 });
    }
    else
    {
        CLOG_PROD("ERROR! Can't initialize processes monitoring!");
        return;
    }

    int port = 1111;
    std::string ip_address = "127.0.0.1";
    bool is_sockets_blocking = true;
    int timeout = 5;
    if (!InitializeSockets(port, ip_address, is_sockets_blocking, timeout))
    {
        CLOG_PROD("ERROR! Can't initialize sockets!");
        return;
    }

    m_p_acceptor_socket->StartServer( );
}

bool CService::InitializeLogger(const std::string& path_to_log_file, ELogLevel level)
{
    m_log_stream = std::make_unique<std::fstream>(path_to_log_file,
                                                  std::ios_base::out);
    if (m_log_stream->is_open( ))
    {
        CLOG_START_CREATION( );

        CLOG_SET_LOG_NAME("Logger");
        CLOG_SET_LOG_LEVEL(level);
        CLOG_SET_LOG_CONFIG(ELogConfig::LOG_NAME, ELogConfig::LOG_LEVEL,
                            ELogConfig::CALL_TIME, ELogConfig::THREAD_ID, ELogConfig::FILE_NAME,
                            ELogConfig::FUNCTION_NAME, ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE,
                            ELogConfig::PARAMS);

        CLOG_ADD_SAFE_STREAM(*m_log_stream);

        CLOG_BUILD( );

        CLOG_END_CREATION( );
        return true;
    }
    return false;
}

bool CService::InitializeThreadPool(size_t num_threads)
{
    CLOG_DEBUG_START_FUNCTION( );
    m_p_thread_pool = std::make_shared<CThreadPool>(num_threads, m_stop_event);
    CLOG_TRACE_VAR_CREATION(m_p_thread_pool);
    CLOG_DEBUG_END_FUNCTION( );
    return true;
}

bool CService::InitializeLogicalDiscMonitoring(const std::chrono::duration<int>& tick,
                                               const std::string& path_to_file,
                                               EMemoryConvertType measure_in)
{
    CLOG_DEBUG_START_FUNCTION( );
    CHardwareStatusSpecification* specification = new CHardwareStatusSpecification(
        tick, path_to_file, measure_in);
    CLOG_TRACE_VAR_CREATION(specification);
    m_disks_monitor = std::make_unique<CLogicalDiskInfoMonitoring>(m_stop_event,
                                                                   specification, 
                                                                   m_disks_json);
    CLOG_TRACE_VAR_CREATION(m_disks_monitor);
    CLOG_DEBUG_END_FUNCTION( );
    return true;
}

bool CService::InitializeProcessesMonitoring(const std::chrono::duration<int>& tick,
                                             const std::string& path_to_file,
                                             EMemoryConvertType measure_in)
{
    m_processes_monitor = std::make_unique<CProcessesInfoMonitoring>(
        tick, path_to_file, measure_in, m_stop_event, m_processes_json);
    CLOG_DEBUG_START_FUNCTION( );
    CLOG_TRACE_VAR_CREATION(m_processes_monitor);
    CLOG_DEBUG_END_FUNCTION( );
    return m_processes_monitor->Initialize( );
}

bool CService::InitializeSockets(int port, const std::string& ip_address,
                                 bool is_sockets_blocking, int timeout)
{
    CLOG_DEBUG_START_FUNCTION( );
    CDataReceiver json_data(m_processes_json, m_disks_json);
    CLOG_TRACE_VAR_CREATION(json_data);
    m_p_acceptor_socket = std::make_unique<CAcceptorWrapper>(port, ip_address,
                                                             m_stop_event, 
                                                             m_p_thread_pool, 
                                                             is_sockets_blocking,
                                                             timeout,
                                                             std::move(json_data));
    CLOG_TRACE_VAR_CREATION(m_p_acceptor_socket);

    CLOG_DEBUG_END_FUNCTION( );
    return true;
}

CService* CService::m_p_service = nullptr;

CService::CService(const ServiceParameters& parameters)
  : m_name(parameters.name),
    m_display_name(parameters.display_name),
    m_start_type(parameters.start_type),
    m_error_control_type(parameters.err_ctrl_type),
    m_status_handle(nullptr),
    m_status{
        SERVICE_WIN32_OWN_PROCESS,
        SERVICE_START_PENDING,
        parameters.accepted_cmds,
        NO_ERROR,
        0,
        0,
        0}
{ }

void CService::SetStatus(DWORD state, DWORD error_code, DWORD wait_hint)
{
    m_status.dwCurrentState = state;
    m_status.dwWin32ExitCode = error_code;
    m_status.dwWaitHint = wait_hint;

    ::SetServiceStatus(m_status_handle, &m_status);
}

DWORD WINAPI CService::ServiceCtrlHandler(
    DWORD control_code, DWORD event_type,
    void* event_data, void* context) 
{
    if (control_code == SERVICE_CONTROL_STOP)
    {
        m_p_service->Stop();
    }

    return 0;
}

void WINAPI CService::SvcMain(DWORD argc, CHAR** argv) 
{
    assert(m_p_service);

    m_p_service->m_status_handle = ::RegisterServiceCtrlHandlerEx(
        m_p_service->GetName(),
        ServiceCtrlHandler, NULL);

    if (!m_p_service->m_status_handle)
    {
        return;
    }

    m_p_service->Start(argc, argv);
}

bool CService::Run()
{
    m_p_service = this;

    CHAR* name = const_cast<CString&>(m_name).GetBuffer();

    SERVICE_TABLE_ENTRY table_entry[] =
    {
        { name, SvcMain },
        { nullptr, nullptr }
    };

    return ::StartServiceCtrlDispatcher(table_entry) == TRUE;
}

const CString& CService::GetName() const 
{ return m_name;}

const CString& CService::GetDisplayName() const 
{ return m_display_name;}

// Chupakabra: returning copy of var, const redundant
const DWORD CService::GetStartType() const
{ return m_start_type;}

// Chupakabra: returning copy of var, const redundant
const DWORD CService::GetErrorControlType() const
{ return m_error_control_type;}

void CService::OnStart(DWORD, CHAR**)
{
    m_main_thread = std::thread([this]()
    {
        RunServer();
    });
}

void CService::OnStop() 
{
    CLOG_DEBUG_START_FUNCTION( );
    m_stop_event.Set();
    CLOG_DEBUG("Stop event setted");
    m_p_acceptor_socket->StopSocket();
    CLOG_DEBUG("Acceptor socket stopped!");
    m_main_thread.join();
    CLOG_TRACE("Main thread joined stopped!");
    m_p_acceptor_socket.reset( );
    CLOG_TRACE("Acceptor socket deleted!");
    m_p_thread_pool.reset( );
    CLOG_TRACE("Thread pool deleted!");
    CLOG_TRACE("Main logger deleted");
    CLOG_DEBUG_END_FUNCTION( );
    CLOG_DESTROY( );
}

void CService::Start(DWORD argc, CHAR** argv)
{
    SetStatus(SERVICE_START_PENDING);
    OnStart(argc, argv);
    SetStatus(SERVICE_RUNNING);
}

void CService::Stop() 
{
    SetStatus(SERVICE_STOP_PENDING);
    OnStop();
    SetStatus(SERVICE_STOPPED);
}
