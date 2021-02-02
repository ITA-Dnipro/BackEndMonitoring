cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

if(UNIX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
endif(UNIX)

link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(.)
link_directories(${CMAKE_BINARY_DIR}/Sockets)

include_directories(BackEndMonitoringServer/include
	${CMAKE_SOURCE_DIR}
	${CMAKE_SOURCE_DIR}/CLogger/include
	${CMAKE_SOURCE_DIR}/Sockets/BackEndMonitoringSockets/include
	${CMAKE_SOURCE_DIR}/3rdParty/include
    ${CMAKE_SOURCE_DIR}/utils/include)

add_executable(Server
	${UTILS}
	${CMAKE_SOURCE_DIR}/3rdParty/include/pugixml.cpp
	${CMAKE_SOURCE_DIR}/utils/include/Utils.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CStringCleaner.cpp
	${CMAKE_SOURCE_DIR}/utils/include/StrToNumWrapper.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CNumericTypesParser.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CReadFileWrapper.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CDataReader.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CXMLDataReader.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CHDDInfoSettings.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CProcessesInfoSettings.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CThreadPoolSettings.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CComunicationSettings.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CServerSettings.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CTimeSettings.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CLoggingSettings.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CEvent.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CThreadPool.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CJSONFormatter.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CJSONFormatSaver.cpp
	BackEndMonitoringServer/src/CCommandLineHandler.cpp
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
	BackEndMonitoringServer/src/CProcessesInfoMonitoring.cpp)

target_link_libraries(Server CLogger)
target_link_libraries(Server Sockets)

