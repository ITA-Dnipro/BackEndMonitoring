#pragma once

#include "CThreadSafeVariable.h"
#include "CEvent.h"
#include "Sockets/BackEndMonitoringSockets/include/CAcceptorWrapper.h"
#include "CJSONFormatterProcess.h"
#include "CJSONFormatterLogicalDisk.h"

class CThreadPool;
class CAcceptorWrapper;
enum class EMemoryConvertType;
class CProcessInfo;
class CHardwareStatusSpecification;
class CContainerOfProcesses;
class CContainerOfLogicalDisk;
class CProcessesInfoMonitoring;
class CLogicalDiskInfoMonitoring;


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
    bool InitializeLogger(const std::string& path_to_log_file, ELogLevel level);
    bool InitializeThreadPool(size_t num_threads);
    bool InitializeLogicalDiscMonitoring(const std::chrono::duration<int>& tick,
                                         const std::string& path_to_file,
                                         EMemoryConvertType measure_in);
    bool InitializeProcessesMonitoring(const std::chrono::duration<int>& tick,
                                       const std::string& path_to_file,
                                       EMemoryConvertType measure_in);
    bool InitializeSockets(int port, const std::string& ip_address,
                           bool is_sockets_blocking, int timeout);
private:
    CEvent m_stop_event;
    CThreadSafeVariable<CJSONFormatterProcess> m_processes_json;
    CThreadSafeVariable<CJSONFormatterLogicalDisk> m_disks_json;
    SERVICE_STATUS m_status;
    std::thread m_main_thread;
    std::shared_ptr<CThreadPool> m_p_thread_pool;
    std::shared_ptr <CProcessesInfoMonitoring> m_processes_monitor;
    std::shared_ptr<CLogicalDiskInfoMonitoring> m_disks_monitor;
    CString m_name;
    CString m_display_name;
    DWORD m_start_type;
    DWORD m_error_control_type;
    std::unique_ptr<CAcceptorWrapper> m_p_acceptor_socket;
    std::unique_ptr<std::fstream> m_log_stream;
    static CService* m_p_service;
    SERVICE_STATUS_HANDLE m_status_handle;  
};
