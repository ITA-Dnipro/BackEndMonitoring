#pragma once

#include "CService.h"

struct ServiceParameters
{
    const CString& name = "BackendMonitoringService";
    const CString& display_name = "Backend monitoring";
    DWORD start_type = SERVICE_DEMAND_START;
    DWORD err_ctrl_type = SERVICE_ERROR_NORMAL;
    DWORD accepted_cmds = SERVICE_ACCEPT_STOP;
};

class CWindowsService : public CService
{
public:
    explicit CWindowsService(const ServiceParameters& parameters);

    const CString& GetName() const;
    const CString& GetDisplayName() const;
    const DWORD GetStartType() const;
    const DWORD GetErrorControlType() const;

    [[nodiscard]] bool Run();

private:
    static void WINAPI SvcMain(DWORD argc, CHAR** argv);

    static DWORD WINAPI ServiceCtrlHandler(
        DWORD control_code,
        DWORD event_type,
        void* event_data,
        void* context);

    void SetStatus(
        DWORD state,
        DWORD exit_code = NO_ERROR,
        DWORD wait_hint = 0);

    void Start(DWORD argc, CHAR** argv);
    void Stop();
    void OnStart(DWORD, CHAR**);
    void OnStop();

private:
    static CWindowsService* m_p_instance;
    SERVICE_STATUS m_status;
    std::thread m_main_thread;
    CString m_name;
    CString m_display_name;
    DWORD m_start_type;
    DWORD m_error_control_type;
    SERVICE_STATUS_HANDLE m_status_handle;
};
