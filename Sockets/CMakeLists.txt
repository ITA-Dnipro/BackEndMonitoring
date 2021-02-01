cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

link_directories(../packages/CLogger/Debug/linux)

include_directories(./BackEndMonitoringSockets/include)
include_directories(../3rdParty/include)
include_directories(../utils/include)
include_directories(..)

add_library(Sockets ../utils/include/LinuxUtils.cpp
        BackEndMonitoringSockets/src/CSocket.cpp
        BackEndMonitoringSockets/src/CAcceptor.cpp
        BackEndMonitoringSockets/src/CAcceptorWrapper.cpp
        BackEndMonitoringSockets/src/CConnector.cpp
        BackEndMonitoringSockets/src/CClientConnectionHandler.cpp
        BackEndMonitoringSockets/src/CConnectorWrapper.cpp
        BackEndMonitoringSockets/src/CServiceConnectionHandler.cpp
        BackEndMonitoringSockets/src/CSocketWrapper.cpp
        BackEndMonitoringSockets/src/CDataReceiver.cpp
        ../utils/include/CThreadPool.cpp
        ../utils/include/CEvent.cpp)

target_link_libraries(Sockets CLogger)
