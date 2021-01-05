#include "Pch.h"

#include "BMService.h"
#include "ServiceInstaller.h"

int _tmain(int argc, TCHAR* argv[]) 
{
    BMService service;

    if (argc > 1)
    {
        if (!_tcscmp(argv[1], _T("install"))) 
        {
            _tprintf(_T("Installing service\n"));
            if (!ServiceInstaller::Install(service)) 
            {
                _tprintf(_T("Couldn't install service: %d\n"), ::GetLastError());
                return -1;
            }

            _tprintf(_T("Service installed\n"));
            return 0;
        }
    
        if (!_tcscmp(argv[1], _T("uninstall")))
        {
            _tprintf(_T("Uninstalling service\n"));
            if (!ServiceInstaller::Uninstall(service))
            {
                _tprintf(_T("Couldn't uninstall service: %d\n"), ::GetLastError());
                return -1;
            }

            _tprintf(_T("Service uninstalled\n"));
            return 0;
        }

        _tprintf(_T("Invalid argument\n"));
        return -1;
    }
  
    service.Run();

    return 0;
}
