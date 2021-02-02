cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_SOURCE_DIR}/packages/CLogger/Debug/linux)

include_directories(
        BackEndMonitoringSockets/include
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/CLogger/include
	${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
        ${CMAKE_SOURCE_DIR}/3rdParty/include
        ${CMAKE_SOURCE_DIR}/utils/include)

add_library(Sockets 
	${CMAKE_SOURCE_DIR}/utils/include/LinuxUtils.cpp
        BackEndMonitoringSockets/src/CSocket.cpp
        BackEndMonitoringSockets/src/CAcceptor.cpp
        BackEndMonitoringSockets/src/CAcceptorWrapper.cpp
        BackEndMonitoringSockets/src/CConnector.cpp
        BackEndMonitoringSockets/src/CClientConnectionHandler.cpp
        BackEndMonitoringSockets/src/CConnectorWrapper.cpp
        BackEndMonitoringSockets/src/CServiceConnectionHandler.cpp
        BackEndMonitoringSockets/src/CSocketWrapper.cpp
        BackEndMonitoringSockets/src/CDataReceiver.cpp
        ${CMAKE_SOURCE_DIR}/utils/include/CThreadPool.cpp
        ${CMAKE_SOURCE_DIR}/utils/include/CEvent.cpp
        ${CMAKE_SOURCE_DIR}/utils/include/Utils.cpp
        ${CMAKE_SOURCE_DIR}/utils/include/LinuxUtils.cpp)

target_link_libraries(Sockets CLogger)
