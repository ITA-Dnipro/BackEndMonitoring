#include "stdafx.h"

#include "CServiceHandler.h"
#include "Utils.h"

#if defined(_WIN64) || defined(_WIN32)
class ServiceHandle
{
public:
    explicit ServiceHandle(SC_HANDLE handle)
      : m_handle(handle) {}

    ServiceHandle(const ServiceHandle&) = delete;
    ServiceHandle(ServiceHandle&&) = delete;

    ~ServiceHandle()
    {
        if (nullptr != m_handle)
        {
            if(::CloseServiceHandle(m_handle) == 0)
            {
                Utils::DisplayError("Failed to close the service handle");
            }
        }
    }

    SC_HANDLE GetHandle() const
    {
        return m_handle;
    }

private:
    SC_HANDLE m_handle = nullptr;
};

ServiceHandler::ServiceHandler(std::unique_ptr<CService> service)
  : m_p_service(std::move(service))
{ }

bool ServiceHandler::Install() const
{
    bool success = false;
    CLOG_DEBUG_START_FUNCTION();
    Utils::DisplayMessage("Installing service");
    success = true;
    CLOG_TRACE_VAR_CREATION(success);
    do
    {
        CString escaped_path;
        if (!CService::GetModulePath(escaped_path))
        {
            Utils::DisplayError("Failed to get module file name");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        CService::EscapePath(escaped_path);

        const auto service_control_manager = std::make_unique<ServiceHandle>(
            ::OpenSCManager(
                nullptr, nullptr,
                SC_MANAGER_CONNECT |
                SC_MANAGER_CREATE_SERVICE));

        CLOG_TRACE_VAR_CREATION(service_control_manager);
        if (service_control_manager->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to open service control manager");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        auto service = std::make_unique<ServiceHandle>(
            ::CreateService(
                service_control_manager->GetHandle(),
                m_p_service->GetName(),
                m_p_service->GetDisplayName(),
                SERVICE_QUERY_STATUS | SERVICE_START,
                SERVICE_WIN32_OWN_PROCESS,
                m_p_service->GetStartType(),
                m_p_service->GetErrorControlType(),
                escaped_path,
                nullptr,
                nullptr,
                nullptr,
                nullptr,
                nullptr));
        CLOG_TRACE_VAR_CREATION(service);
        if (service->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to create service");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        Start();
    } while (false);

    success ? Utils::DisplayMessage("Service installed")
            : Utils::DisplayMessage("Failed to install the service");
    CLOG_TRACE_VAR_CREATION(success);
    CLOG_DEBUG_END_FUNCTION();
    return success;
}

bool ServiceHandler::Uninstall() const
{
    Utils::DisplayMessage("Uninstalling service");

    bool success = false;
    CLOG_DEBUG_START_FUNCTION();
    success = true;
    CLOG_TRACE_VAR_CREATION(success);
    do
    {
        auto service_control_manager = std::make_unique<ServiceHandle>(
            ::OpenSCManager(
                nullptr, nullptr,
                SC_MANAGER_CONNECT));
        CLOG_TRACE_VAR_CREATION(service_control_manager);
        if (service_control_manager->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to open service control manager");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        auto service = std::make_unique<ServiceHandle>(
            ::OpenService(
                service_control_manager->GetHandle(),
                m_p_service->GetName(),
                SERVICE_QUERY_STATUS |
                DELETE));

        if (service->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to open service");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        Stop();

        if (::DeleteService(service->GetHandle()) == 0)
        {
            Utils::DisplayError("Failed to delete the service");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }
    } while (false);

    success ? Utils::DisplayMessage("Service uninstalled")
            : Utils::DisplayMessage("Failed to uninstall the service");
    CLOG_TRACE_VAR_CREATION(success);
    CLOG_DEBUG_END_FUNCTION();
    return success;
}

bool ServiceHandler::Start() const
{
    Utils::DisplayMessage("Starting the service");
    bool success = false;
    CLOG_DEBUG_START_FUNCTION();
    success = true;
    CLOG_TRACE_VAR_CREATION(success);
    do
    {
        auto service_control_manager = std::make_unique<ServiceHandle>(
            ::OpenSCManager(
                nullptr, nullptr,
                SC_MANAGER_CONNECT));
        CLOG_TRACE_VAR_CREATION(service_control_manager);

        if (service_control_manager->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to open the service control manager");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        auto service = std::make_unique<ServiceHandle>(
            ::OpenService(
                service_control_manager->GetHandle(),
                m_p_service->GetName(),
                SERVICE_QUERY_STATUS |
                SERVICE_START));

        if (service->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to open the service");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        if (StartService(service->GetHandle(), 0, NULL) == 0)
        {
            Utils::DisplayError("Failed to start the service");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }
    } while (false);

    success ? Utils::DisplayMessage("Service started")
            : Utils::DisplayMessage("Failed to start the service");
    CLOG_TRACE_VAR_CREATION(success);
    CLOG_DEBUG_END_FUNCTION();
    return success;
}

bool ServiceHandler::Stop() const
{
    Utils::DisplayMessage("Stopping the service");

    bool success = false;
    CLOG_DEBUG_START_FUNCTION();
    success = true;
    CLOG_TRACE_VAR_CREATION(success);
    do
    {
        auto service_control_manager = std::make_unique<ServiceHandle>(
            ::OpenSCManager(
                nullptr, nullptr,
                SC_MANAGER_CONNECT));
        CLOG_TRACE_VAR_CREATION(service_control_manager);

        if (service_control_manager->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to open the service control manager");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        auto service = std::make_unique<ServiceHandle>(
            ::OpenService(
                service_control_manager->GetHandle(),
                m_p_service->GetName(),
                SERVICE_QUERY_STATUS |
                SERVICE_STOP));

        if (service->GetHandle() == nullptr)
        {
            Utils::DisplayError("Failed to open the service");
            success = false;
            CLOG_TRACE_VAR_CREATION(success);
            break;
        }

        SERVICE_STATUS status = {};
        CLOG_TRACE_VAR_CREATION(status);
        if (::ControlService(service->GetHandle(), SERVICE_CONTROL_STOP, &status) != 0)
        {
            while (::QueryServiceStatus(service->GetHandle(), &status) != 0)
            {
                if (status.dwCurrentState != SERVICE_STOP_PENDING)
                {
                    // TODO: Add information
                    break;
                }
            }

            if (status.dwCurrentState != SERVICE_STOPPED)
            {
                success = false;
                CLOG_TRACE_VAR_CREATION(success);
                break;
            }
        }
        else
        {
            Utils::DisplayError("Didn't control service");
        }
    } while (false);

    success ? Utils::DisplayMessage("Service stopped")
            : Utils::DisplayMessage("Failed to stop the service");
    CLOG_TRACE_VAR_CREATION(success);
    CLOG_DEBUG_END_FUNCTION();
    return success;
}

bool ServiceHandler::Run() const
{
    return m_p_service->Run();
}
#endif
