cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(.)
link_directories(${CMAKE_BINARY_DIR}/Sockets)
link_directories(${CMAKE_BINARY_DIR}/CLient)

include_directories(${CMAKE_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClientCLI/include
		${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
		${CMAKE_SOURCE_DIR}/CLogger/include
		${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
		${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
		${CMAKE_SOURCE_DIR}/3rdParty/include
		${CMAKE_SOURCE_DIR}/utils/include)

set(CLIENTCLI_SRC_DIR ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClientCLI/src)

add_executable(ClientCLI
		${UTILS_SRC_DIR}/Utils.cpp
		${UTILS_SRC_DIR}/CStringCleaner.cpp
		${CLIENTCLI_SRC_DIR}/BackEndMonitoringClientCLI.cpp
		${CLIENTCLI_SRC_DIR}/CClient.cpp
		${CLIENTCLI_SRC_DIR}/CClientView.cpp)

# Link these libraries to this build
target_link_libraries(ClientCLI CLogger)
target_link_libraries(ClientCLI Sockets)
target_link_libraries(ClientCLI Client)
