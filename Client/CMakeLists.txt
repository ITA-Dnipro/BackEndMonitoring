cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(.)
link_directories(${CMAKE_BINARY_DIR}/Sockets)

include_directories(${CMAKE_SOURCE_DIR}
	BackEndMonitoringClient/include
	${CMAKE_SOURCE_DIR}/CLogger/include
	${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
	${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
	${CMAKE_SOURCE_DIR}/3rdParty/include
	${CMAKE_SOURCE_DIR}/utils/include)

add_executable(Client
	BackEndMonitoringClient/src/BackEndMonitoringClient.cpp
	BackEndMonitoringClient/src/CClient.cpp
	BackEndMonitoringClient/src/CClientView.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CReadFileWrapper.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CNumericTypesParser.cpp
	${CMAKE_SOURCE_DIR}/utils/include/Utils.cpp
	${CMAKE_SOURCE_DIR}/utils/include/StrToNumWrapper.cpp
	${CMAKE_SOURCE_DIR}/utils/include/CStringCleaner.cpp)

target_link_libraries(Client CLogger)
target_link_libraries(Client Sockets)
