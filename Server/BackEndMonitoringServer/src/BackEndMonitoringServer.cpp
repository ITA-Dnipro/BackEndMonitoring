#include "stdafx.h"

#include "CEvent.h"
#include "EMemoryCountType.h"
#include "CProcess.h"
#include "CContainerOfProcesses.h"
#include "CThreadSafeVariable.h"
#include "CJSONFormatter.h"
#include "CJSONFormatterProcess.h"
#include "CProcessesMonitoringLifeCycle.h"

int main(int argc, char** argv)
{
    CEvent stop;
    CThreadSafeVariable<CJSONFormatterProcess> jsonf;
    CProcessesMonitoringLifeCycle processes(std::chrono::seconds(10),
                                  "F:\\Git\\BackEndMonitoring\\log.json",
                                  EMemoryCountType::KILOBYTES, stop, jsonf);
    processes.Initialize( );
    processes.ThreadLifeCycle( );
    return 0;
}