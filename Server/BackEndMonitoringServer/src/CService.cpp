#include "stdafx.h"

#include "CService.h"
#include "CThreadPool.h"
#include "Clogger/include/Log.h"

// We need this to test the service
#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"

void CService::RunServer()
{
    std::fstream stream("Log.txt", std::ios_base::out);
    CLogBuilder builder("Logger", ELogLevel::DEBUG_LEVEL);
    builder.AddThreadUnsafeStream(stream).SetLogConfig(ELogConfig::CALL_TIME,
        ELogConfig::FILE_NAME, ELogConfig::FUNCTION_NAME,
        ELogConfig::LINE_NUMBER, ELogConfig::MESSAGE, ELogConfig::PARAMS);
    auto logger = builder.BuildSharedLog();

    size_t num_threads = 20;
    int port = 1111;
    std::string ip_address = "127.0.0.1";
    WRITE_DEBUG(*logger, "Start server");

    m_thread_pool = std::make_shared<CThreadPool>(num_threads, m_stop_event);
    m_acceptor_socket = std::make_unique<CAcceptorWrapper>(port, ip_address, 
        m_stop_event, m_thread_pool, logger);

    m_acceptor_socket->StartServer();
}

CService* CService::m_service = nullptr;

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
        m_service->Stop();
    }

    return 0;
}

void WINAPI CService::SvcMain(DWORD argc, CHAR** argv) 
{
    assert(m_service);

    m_service->m_status_handle = ::RegisterServiceCtrlHandlerEx(
        m_service->GetName(),
        ServiceCtrlHandler, NULL);

    if (!m_service->m_status_handle)
    {
        return;
    }

    m_service->Start(argc, argv);
}

bool CService::Run()
{
    m_service = this;

    CHAR* name = const_cast<CString&>(m_name).GetBuffer();

    SERVICE_TABLE_ENTRY table_entry[] =
    {
        { name, SvcMain },
        { nullptr, nullptr }
    };

    return ::StartServiceCtrlDispatcher(table_entry) == TRUE;
}

const CString& CService::GetName() const 
{ 
    return m_name; 
}

const CString& CService::GetDisplayName() const 
{ 
    return m_display_name;
}

const DWORD CService::GetStartType() const
{ 
    return m_start_type;
}

const DWORD CService::GetErrorControlType() const
{
    return m_error_control_type;
}

void CService::OnStart(DWORD, CHAR**)
{
    m_main_thread = std::thread([this]()
    {
        RunServer();
    });
}

void CService::OnStop() 
{
    m_stop_event.Set();
    m_acceptor_socket->StopSocket();
    m_main_thread.join();
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
