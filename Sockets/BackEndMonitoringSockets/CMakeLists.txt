#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

#------------------------------ SRC/INCLUDE DIRS' VARS --------------------------------#

set(SOCKETS_SRC_DIR ${CMAKE_SOURCE_DIR}/Sockets/BackEndMonitoringSockets/src)

#------------------------------------ INCLUDE DIRS -------------------------------------#

include_directories(${CMAKE_SOURCE_DIR}
		${NLOHMANN_JSON_INCLUDE_DIR}
#		${CMAKE_SOURCE_DIR}/3rdParty/include
		${CMAKE_SOURCE_DIR}/Sockets/BackEndMonitoringSockets/include
		${CMAKE_SOURCE_DIR}/CLogger/include
		${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
		${CMAKE_SOURCE_DIR}/3rdParty/include
		${CMAKE_SOURCE_DIR}/utils/include)

#--------------------------------- EXECUTE CONFIGS -------------------------------------#

add_library(Sockets
		${PLATFORM_SPECIFIC_UTILS}
		${SOCKETS_SRC_DIR}/CSocket.cpp
		${SOCKETS_SRC_DIR}/CSockAddress.cpp
		${SOCKETS_SRC_DIR}/CAcceptor.cpp
		${SOCKETS_SRC_DIR}/CServiceHost.cpp
		${SOCKETS_SRC_DIR}/CConnector.cpp
		${SOCKETS_SRC_DIR}/CClientConnectionHandler.cpp
		${SOCKETS_SRC_DIR}/CClientConnectorHost.cpp
		${SOCKETS_SRC_DIR}/CServiceConnectionHandler.cpp
		${SOCKETS_SRC_DIR}/CSocketWrapper.cpp
		${SOCKETS_SRC_DIR}/CDataProvider.cpp
		${UTILS_SRC_DIR}/CThreadPool.cpp
		${UTILS_SRC_DIR}/CRequestFrame.cpp
		${UTILS_SRC_DIR}/CRequestHandler.cpp
		${UTILS_SRC_DIR}/CResponseFrame.cpp
		${UTILS_SRC_DIR}/CResponseHandler.cpp
		${UTILS_SRC_DIR}/CInteractionFrame.cpp
		${UTILS_SRC_DIR}/CEvent.cpp
		${UTILS_SRC_DIR}/Utils.cpp)

#----------------------------------- TARGET LIBS ---------------------------------------#

target_link_libraries(Sockets CLogger)
target_link_libraries(Sockets Guid)
