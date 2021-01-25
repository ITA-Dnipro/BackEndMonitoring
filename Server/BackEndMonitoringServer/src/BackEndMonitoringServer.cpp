#include "stdafx.h"

#include "CEvent.h"
#include "EMemoryConvertType.h"
#include "CProcessInfo.h"
#include "CContainerOfProcesses.h"
#include "CThreadSafeVariable.h"
#include "CJSONFormatter.h"
#include "CJSONFormatterProcess.h"
#include "CJSONFormatterLogicalDisk.h"
#include "CProcessesInfoMonitoring.h"
#include "CLogicalDiskInfoMonitoring.h"

int main(int argc, char** argv)
{
    /*
    CEvent stop;
    CThreadSafeVariable<CJSONFormatterProcess> jsonf;
    CProcessesInfoMonitoring processes(std::chrono::seconds(10),
                                  "F:\\Git\\BackEndMonitoring\\log.json",
                                  EMemoryConvertType::KILOBYTES, stop, jsonf);
    processes.Initialize( );
    processes.StartMonitoringInfo( );
    */


    CEvent stop;
    CThreadSafeVariable<CJSONFormatterLogicalDisk> jsonf;
    CHardwareStatusSpecification specification_from_xml(
        std::chrono::duration<int>(1), "info.json",
        EMemoryConvertType::GIGABYTES);
    CLogicalDiskInfoMonitoring logical_disks(stop, &specification_from_xml, jsonf);

    logical_disks.StartMonitoringInfo();


    return 0;
}