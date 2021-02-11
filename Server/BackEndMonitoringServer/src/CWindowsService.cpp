#include "stdafx.h"

#include "Utils.h"

#include "CWindowsService.h"

CWindowsService* CWindowsService::m_p_instance = nullptr;

bool CWindowsService::Run()
{
    m_p_instance = this;

    CHAR* name = const_cast<CString&>(m_name).GetBuffer();

    SERVICE_TABLE_ENTRY table_entry[] =
    {
        { name, SvcMain },
        { nullptr, nullptr }
    };

    return ::StartServiceCtrlDispatcher(table_entry) == TRUE;
}

CWindowsService::CWindowsService(const ServiceParameters& parameters)
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
        0 }
{ }

bool CWindowsService::GetModulePath(CString& module_path)
{
    bool success = true;

    LPSTR path = module_path.GetBufferSetLength(MAX_PATH);

    if (::GetModuleFileName(nullptr, path, MAX_PATH) == 0)
    {
        Utils::DisplayError("Failed to get module file name");
        success = false;
    }

    module_path.ReleaseBuffer();
    return success;
}

bool CWindowsService::EscapePath(CString& path)
{
    path.Remove('\"');
    path = '\"' + path + '\"';
    return true;
}

void CWindowsService::SetStatus(DWORD state, DWORD error_code, DWORD wait_hint)
{
    m_status.dwCurrentState = state;
    m_status.dwWin32ExitCode = error_code;
    m_status.dwWaitHint = wait_hint;

    ::SetServiceStatus(m_status_handle, &m_status);
}

DWORD WINAPI CWindowsService::ServiceCtrlHandler(
    DWORD control_code, DWORD event_type,
    void* event_data, void* context)
{
    if (control_code == SERVICE_CONTROL_STOP)
    {
        m_p_instance->Stop( );
    }

    return 0;
}

void WINAPI CWindowsService::SvcMain(DWORD argc, CHAR** argv)
{
    assert(m_p_instance);

    m_p_instance->m_status_handle = ::RegisterServiceCtrlHandlerEx(
        m_p_instance->GetName( ),
        ServiceCtrlHandler, NULL);

    if (!m_p_instance->m_status_handle)
    {
        return;
    }

    m_p_instance->Start(argc, argv);
}

const CString& CWindowsService::GetName( ) const
{
    return m_name;
}

const CString& CWindowsService::GetDisplayName( ) const
{
    return m_display_name;
}

// Chupakabra: returning copy of var, const redundant
const DWORD CWindowsService::GetStartType( ) const
{
    return m_start_type;
}

// Chupakabra: returning copy of var, const redundant
const DWORD CWindowsService::GetErrorControlType( ) const
{
    return m_error_control_type;
}

void CWindowsService::OnStart(DWORD, CHAR**)
{
    m_main_thread = std::thread([this] ( )
    {
        RunServer( );
    });
}

void CWindowsService::OnStop()
{
    CLOG_DEBUG_START_FUNCTION();
    m_stop_event.Set();
    CLOG_DEBUG("Stop event setted");
    m_p_acceptor_socket->StopSocket();
    CLOG_DEBUG("Acceptor socket stopped!");
    m_main_thread.join();
    CLOG_TRACE("Main thread joined stopped!");
    m_p_acceptor_socket.reset();
    CLOG_TRACE("Acceptor socket deleted!");
    m_p_thread_pool.reset();
    CLOG_TRACE("Thread pool deleted!");
    CLOG_TRACE("Main logger deleted");
    CLOG_DEBUG_END_FUNCTION( );
    CLOG_DESTROY();
}

void CWindowsService::Start(DWORD argc, CHAR** argv)
{
    SetStatus(SERVICE_START_PENDING);
    OnStart(argc, argv);
    SetStatus(SERVICE_RUNNING);
}

void CWindowsService::Stop()
{
    SetStatus(SERVICE_STOP_PENDING);
    OnStop( );
    SetStatus(SERVICE_STOPPED);
}
