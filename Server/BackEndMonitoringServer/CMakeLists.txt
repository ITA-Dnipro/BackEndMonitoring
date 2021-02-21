cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)


link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(..)
link_directories(${CMAKE_BINARY_DIR}/Sockets)

include_directories(${CMAKE_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
		${CMAKE_SOURCE_DIR}/CLogger/include
		${CMAKE_SOURCE_DIR}/Sockets/BackEndMonitoringSockets/include
		${CMAKE_SOURCE_DIR}/3rdParty/include
		${CMAKE_SOURCE_DIR}/utils/include)

set(SERVER_SRC_DIR ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/src)

add_executable(Server
		${PLATFORM_SPECIFIC_UTILS}
		${THIRD_PARTY_DIR}/pugixml.cpp
		${UTILS_SRC_DIR}/Utils.cpp
		${UTILS_SRC_DIR}/CStringCleaner.cpp
		${UTILS_SRC_DIR}/StrToNumWrapper.cpp
		${UTILS_SRC_DIR}/CNumericTypesParser.cpp
		${UTILS_SRC_DIR}/CReadFileWrapper.cpp
		${UTILS_SRC_DIR}/CDataReader.cpp
		${UTILS_SRC_DIR}/CXMLDataReader.cpp
		${UTILS_SRC_DIR}/CHDDInfoSettings.cpp
		${UTILS_SRC_DIR}/CProcessesInfoSettings.cpp
		${UTILS_SRC_DIR}/CThreadPoolSettings.cpp
		${UTILS_SRC_DIR}/CComunicationSettings.cpp
		${UTILS_SRC_DIR}/CServerSettings.cpp
		${UTILS_SRC_DIR}/CSettings.cpp
		${UTILS_SRC_DIR}/CTimeSettings.cpp
		${UTILS_SRC_DIR}/CLoggingSettings.cpp
		${UTILS_SRC_DIR}/CEvent.cpp
		${UTILS_SRC_DIR}/CThreadPool.cpp
		${UTILS_SRC_DIR}/CJSONFormatter.cpp
		${UTILS_SRC_DIR}/CJSONFormatSaver.cpp
		${SERVER_SRC_DIR}/CCommandLineHandler.cpp
		${SERVER_SRC_DIR}/CContainerOfLogicalDisk.cpp
		${SERVER_SRC_DIR}/CContainerOfProcesses.cpp
		${SERVER_SRC_DIR}/CHardwareStatusSpecification.cpp
		${SERVER_SRC_DIR}/CJSONFormatterLogicalDisk.cpp
		${SERVER_SRC_DIR}/CJSONFormatterProcess.cpp
		${SERVER_SRC_DIR}/CLogicalDiskInfo.cpp
		${SERVER_SRC_DIR}/CLogicalDiskInfoMonitoring.cpp
		${SERVER_SRC_DIR}/CService.cpp
		${SERVER_SRC_DIR}/CServiceHandler.cpp
		${SERVER_SRC_DIR}/CProcessInfo.cpp
		${SERVER_SRC_DIR}/BackEndMonitoringServer.cpp
		${SERVER_SRC_DIR}/CProcessesInfoMonitoring.cpp)

# Link these libraries to this build
target_link_libraries(Server CLogger)
target_link_libraries(Server Sockets)
