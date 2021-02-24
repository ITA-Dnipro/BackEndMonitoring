#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

#------------------------------ SRC/INCLUDE DIRS' VARS --------------------------------#

set(CLIENT_SRC_DIR ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/src)

#------------------------------------ INCLUDE DIRS -------------------------------------#


include_directories(${CMAKE_SOURCE_DIR}
		${NLOHMANN_JSON_INCLUDE_DIR}
		${CMAKE_SOURCE_DIR}/3rdParty/include
		${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
		${CMAKE_SOURCE_DIR}/CLogger/include
		${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
		${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
		${CMAKE_SOURCE_DIR}/utils/include)

#--------------------------------- EXECUTE CONFIGS -------------------------------------#

add_library(Client
		${UTILS_SRC_DIR}/CReadFileWrapper.cpp
		${UTILS_SRC_DIR}/CNumericTypesParser.cpp
		${UTILS_SRC_DIR}/Utils.cpp
		${UTILS_SRC_DIR}/StrToNumWrapper.cpp
		${UTILS_SRC_DIR}/CStringCleaner.cpp
		${CLIENT_SRC_DIR}/CClientController.cpp)

#----------------------------------- TARGET LIBS ---------------------------------------#

target_link_libraries(Client CLogger)
target_link_libraries(Client Guid)
target_link_libraries(Client Sockets)
