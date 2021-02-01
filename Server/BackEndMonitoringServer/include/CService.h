#pragma once

#include "CEvent.h"
#include "Sockets/BackEndMonitoringSockets/include/CAcceptorWrapper.h"

struct ServiceParameters
{
    const CString& name = "BackendMonitoringService";
    const CString& display_name = "Backend monitoring";
    DWORD start_type = SERVICE_DEMAND_START;
    DWORD err_ctrl_type = SERVICE_ERROR_NORMAL;
    DWORD accepted_cmds = SERVICE_ACCEPT_STOP;
};

class CService
{
public:
    explicit CService(const ServiceParameters& parameters);
    
    CService(const CService& other) = delete;
    CService& operator=(const CService& other) = delete;

    CService(CService&& other) = delete;
    CService& operator=(CService&& other) = delete;
    const CString& GetName() const;
    const CString& GetDisplayName() const;
    const DWORD GetStartType() const;
    const DWORD GetErrorControlType() const;
  
    bool Run();

private:
    static DWORD WINAPI ServiceCtrlHandler(
        DWORD control_code, 
        DWORD event_type,
        void* event_data, 
        void* context);

    static void WINAPI SvcMain(DWORD argc, CHAR** argv);

    void SetStatus(
        DWORD state,
        DWORD exit_code = NO_ERROR,
        DWORD wait_hint = 0);

    void Start(DWORD argc, CHAR** argv);
    void Stop();
    void OnStart(DWORD, CHAR**);
    void OnStop();
    void RunServer();
private:
    static CService* m_p_service;
    CString m_name;
    CString m_display_name;
    DWORD m_start_type;
    DWORD m_error_control_type;
    SERVICE_STATUS m_status;
    SERVICE_STATUS_HANDLE m_status_handle;
    std::thread m_main_thread;
    CEvent m_stop_event;
    std::shared_ptr<CThreadPool> m_p_thread_pool;
    std::unique_ptr<CAcceptorWrapper> m_p_acceptor_socket;
    std::unique_ptr<std::fstream> m_log_stream;
};
