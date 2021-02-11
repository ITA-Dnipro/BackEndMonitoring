#pragma once

#include "CThreadSafeVariable.h"
#include "CEvent.h"
#include "CAcceptorWrapper.h"
#include "CJSONFormatterProcess.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CDataReader.h"

class CThreadPool;
class CAcceptorWrapper;
enum class EMemoryConvertType;
class CProcessInfo;
class CHardwareStatusSpecification;
class CContainerOfProcesses;
class CContainerOfLogicalDisk;
class CProcessesInfoMonitoring;
class CLogicalDiskInfoMonitoring;
class CLoggingSettings;
class CThreadPoolSettings;
class CHDDInfoSettings;
class CProcessesInfoSettings;
class CServerSettings;

class CService
{
public:
    CService() = default;

    CService(const CService& other) = delete;
    CService& operator=(const CService& other) = delete;

    CService(CService&& other) = delete;
    CService& operator=(CService&& other) = delete;

    virtual bool Run() = 0;

protected:
    [[nodiscard]] bool InitializeLogger(const std::string& path_to_log_file, ELogLevel level);
    [[nodiscard]] bool InitializeThreadPool(const CThreadPoolSettings& thread_pool_sett);
    [[nodiscard]] bool InitializeLogicalDiscMonitoring(const CHDDInfoSettings& xml_settings);
    [[nodiscard]] bool InitializeProcessesMonitoring(const CProcessesInfoSettings& xml_settings);
    [[nodiscard]] bool InitializeSockets(const CServerSettings& server_sett);

    void RunServer();

protected:
    CEvent m_stop_event;
    std::shared_ptr<CThreadPool> m_p_thread_pool;
    std::unique_ptr<CAcceptorWrapper> m_p_acceptor_socket;
    CThreadSafeVariable<CJSONFormatterProcess> m_processes_json;
    CThreadSafeVariable<CJSONFormatterLogicalDisk> m_disks_json;
    std::shared_ptr <CProcessesInfoMonitoring> m_processes_monitor;
    std::shared_ptr<CLogicalDiskInfoMonitoring> m_disks_monitor;
    std::unique_ptr<std::fstream> m_log_stream;
};
