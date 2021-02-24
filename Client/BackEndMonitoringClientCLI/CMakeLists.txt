#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

#------------------------------ SRC/INCLUDE DIRS' VARS --------------------------------#

set(CLIENTCLI_SRC_DIR ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClientCLI/src)

#------------------------------------ INCLUDE DIRS -------------------------------------#

include_directories(${CMAKE_SOURCE_DIR}
		${NLOHMANN_JSON_INCLUDE_DIR}
		${GUID_INCLUDE_DIR}
		${CMAKE_SOURCE_DIR}/3rdParty/include
		${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClientCLI/include
		${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
		${CMAKE_SOURCE_DIR}/CLogger/include
		${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
		${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
		${CMAKE_SOURCE_DIR}/utils/include)

#--------------------------------- EXECUTE CONFIGS -------------------------------------#

add_executable(ClientCLI
		${UTILS_SRC_DIR}/Utils.cpp
		${UTILS_SRC_DIR}/CRequestFrame.cpp
		${UTILS_SRC_DIR}/CStringCleaner.cpp
		${CLIENTCLI_SRC_DIR}/BackEndMonitoringClientCLI.cpp
		${CLIENTCLI_SRC_DIR}/CClient.cpp
		${CLIENTCLI_SRC_DIR}/CClientView.cpp
		${CLIENTCLI_SRC_DIR}/ClientUtils.cpp
		${CLIENTCLI_SRC_DIR}/CResponseAdapter.cpp)

set_target_properties(ClientCLI PROPERTIES OUTPUT_NAME "Client")

#----------------------------------- TARGET LIBS ---------------------------------------#

target_link_libraries(ClientCLI CLogger)
target_link_libraries(ClientCLI Guid)
target_link_libraries(ClientCLI Sockets)
target_link_libraries(ClientCLI Client)
