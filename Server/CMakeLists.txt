cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(${CMAKE_BINARY_DIR}/Sockets)

include_directories(BackEndMonitoringServer/include)
include_directories(../3rdParty/include)
include_directories(../utils/include)
include_directories(..)

add_executable(Server BackEndMonitoringServer/src/CCommandLineHandler.cpp
        BackEndMonitoringServer/src/CContainerOfLogicalDisk.cpp
        BackEndMonitoringServer/src/CContainerOfProcesses.cpp
        BackEndMonitoringServer/src/CHardwareStatusSpecification.cpp
        BackEndMonitoringServer/src/CJSONFormatterLogicalDisk.cpp
        BackEndMonitoringServer/src/CJSONFormatterProcess.cpp
        BackEndMonitoringServer/src/CLogicalDiskInfo.cpp
        BackEndMonitoringServer/src/CLogicalDiskInfoMonitoring.cpp
        BackEndMonitoringServer/src/CService.cpp
        BackEndMonitoringServer/src/CServiceHandler.cpp
        BackEndMonitoringServer/src/CProcessInfo.cpp
        BackEndMonitoringServer/src/BackEndMonitoringServer.cpp
        BackEndMonitoringServer/src/CProcessesInfoMonitoring.cpp
        ../utils/include/LinuxUtils.cpp
        ../utils/include/Utils.cpp)

target_link_libraries(Client CLogger)
target_link_libraries(Client Sockets)

