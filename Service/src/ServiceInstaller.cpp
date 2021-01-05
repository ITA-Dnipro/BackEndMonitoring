#include "Pch.h"

#include "ServiceInstaller.h"

class ServiceHandle
{
public:
    ServiceHandle(SC_HANDLE handle)
      : m_handle(handle) {}

    ~ServiceHandle() 
    {
        if (m_handle) 
        {
            ::CloseServiceHandle(m_handle);
        }
    }

    operator SC_HANDLE() 
    {
        return m_handle;
    }

private:
    SC_HANDLE m_handle = nullptr;
};

bool ServiceInstaller::Install(const BMService& service)
{
    CString escaped_path;
    TCHAR* module_path = escaped_path.GetBufferSetLength(MAX_PATH);

    if (::GetModuleFileName(nullptr, module_path, MAX_PATH) == 0)
    {
        _tprintf(_T("Couldn't get module file name: %d\n"), ::GetLastError());
        return false;
    }

    escaped_path.ReleaseBuffer();
    escaped_path.Remove(_T('\"'));

    escaped_path = _T('\"') + escaped_path + _T('\"');

    ServiceHandle svc_control_manager = ::OpenSCManager(
        nullptr, nullptr,
        SC_MANAGER_CONNECT | 
        SC_MANAGER_CREATE_SERVICE);

    if (!svc_control_manager) 
    {
        _tprintf(_T("Couldn't open service control manager: %d\n"), ::GetLastError());
        return false;
    }
  
    const CString& depends = service.GetDependencies();
    const CString& account = service.GetAccount();
    const CString& password = service.GetPassword();

    ServiceHandle handle = ::CreateService(
        svc_control_manager,
        service.GetName(),
        service.GetDisplayName(),
        SERVICE_QUERY_STATUS,
        SERVICE_WIN32_OWN_PROCESS,
        service.GetStartType(),
        service.GetErrorControlType(),
        escaped_path,
        nullptr,
        nullptr,
        (depends.IsEmpty() ? nullptr : depends.GetString()),
        (account.IsEmpty() ? nullptr : account.GetString()),
        (password.IsEmpty() ? nullptr : password.GetString()));

    if (!handle) 
    {
        _tprintf(_T("Couldn't create service: %d\n"), ::GetLastError());
        return false;
    }

    return true;
}

bool ServiceInstaller::Uninstall(const BMService& service)
{
    ServiceHandle svc_control_manager = ::OpenSCManager(
        nullptr, nullptr,
        SC_MANAGER_CONNECT);

    if (!svc_control_manager)
    {
        _tprintf(_T("Couldn't open service control manager: %d\n"), ::GetLastError());
        return false;
    }

    ServiceHandle handle = ::OpenService(
        svc_control_manager, service.GetName(),
        SERVICE_QUERY_STATUS | 
        SERVICE_STOP |
        DELETE);

    if (!handle)
    {
        _tprintf(_T("Couldn't open service control manager: %d\n"), ::GetLastError());
        return false;
    }

    SERVICE_STATUS status = {};
    if (::ControlService(handle, SERVICE_CONTROL_STOP, &status))
    {
        _tprintf(_T("Stoping service %s\n"), service.GetName());
    
        while (::QueryServiceStatus(handle, &status)) 
        {
            if (status.dwCurrentState != SERVICE_STOP_PENDING)
            {
                break;
            }
        }

        if (status.dwCurrentState != SERVICE_STOPPED)
        {
            _tprintf(_T("Failed to stop the service\n"));
        } 
        else 
        {
            _tprintf(_T("Service stopped\n"));
        }
    } 
    else
    {
        _tprintf(_T("Didn't control service: %d\n"), ::GetLastError());
    }

    if (!::DeleteService(handle))
    {
        _tprintf(_T("Failed to delete the service: %d\n"), ::GetLastError());
        return false;
    }

    return true;
}
