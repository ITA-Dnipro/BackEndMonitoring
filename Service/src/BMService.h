#pragma once

class BMService {
public:
    BMService(const BMService& other) = delete;
    BMService& operator=(const BMService& other) = delete;

    BMService(BMService&& other) = delete;
    BMService& operator=(BMService&& other) = delete;

    BMService(
        const CString& name = _T("BMService"),
        const CString& display_name = _T("Backend monitoring"),
        DWORD start_type = SERVICE_DEMAND_START,
        DWORD err_ctrl_type = SERVICE_ERROR_NORMAL,
        DWORD accepted_cmds = SERVICE_ACCEPT_STOP,
        const CString& depends = _T(""),
        const CString& account = _T(""),
        const CString& password = _T(""));

    const CString& GetName() const;
    const CString& GetDisplayName() const;
    const DWORD GetStartType() const;
    const DWORD GetErrorControlType() const;
    const CString& GetDependencies() const;
    const CString& GetAccount() const;
    const CString& GetPassword() const;
  
    bool Run();

private:
    static BMService* m_service;
    std::thread m_main_thread;

    static DWORD WINAPI ServiceCtrlHandler(
        DWORD ctrlCode, DWORD evtType,
        void* evtData, void* context);

    static void WINAPI SvcMain(DWORD argc, TCHAR* argv[]);

    CString m_name;
    CString m_display_name;
    DWORD m_start_type;
    DWORD m_error_ctrl_type;
    CString m_depends;
    CString m_account;
    CString m_password;

    SERVICE_STATUS m_status;
    SERVICE_STATUS_HANDLE m_status_handle;
    void SetStatus(DWORD dwState, DWORD dwErrCode = NO_ERROR, DWORD dwWait = 0);

    void Start(DWORD argc, TCHAR* argv[]);
    void Stop();
    void OnStart(DWORD, TCHAR**);
    void OnStop();
};
