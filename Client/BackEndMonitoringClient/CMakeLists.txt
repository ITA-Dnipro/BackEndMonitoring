cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(.)
link_directories(${CMAKE_BINARY_DIR}/Sockets)

include_directories(${CMAKE_SOURCE_DIR}
		${NLOHMANN_JSON_INCLUDE_DIR}
		${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
		${CMAKE_SOURCE_DIR}/CLogger/include
		${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
		${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
		${CMAKE_SOURCE_DIR}/utils/include)

set(CLIENT_SRC_DIR ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/src)

add_library(Client
		${UTILS_SRC_DIR}/CReadFileWrapper.cpp
		${UTILS_SRC_DIR}/CNumericTypesParser.cpp
		${UTILS_SRC_DIR}/Utils.cpp
		${UTILS_SRC_DIR}/StrToNumWrapper.cpp
		${UTILS_SRC_DIR}/CStringCleaner.cpp
		${CLIENT_SRC_DIR}/CClientController.cpp)

# Link these libraries to this build
target_link_libraries(Client CLogger)
target_link_libraries(Client Sockets)