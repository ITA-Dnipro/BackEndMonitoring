cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(.)
link_directories(${CMAKE_BINARY_DIR}/Sockets)

include_directories(./BackEndMonitoringClient/include)
include_directories(../3rdParty/include)
include_directories(../utils/include)
include_directories(..)

add_executable(Client BackEndMonitoringClient/src/BackEndMonitoringClient.cpp
        BackEndMonitoringClient/src/CClient.cpp
        BackEndMonitoringClient/src/CClientView.cpp
        ../utils/include/CReadFileWrapper.cpp
        ../utils/include/CNumericTypesParser.cpp
        ../utils/include/Utils.cpp
        ../utils/include/StrToNumWrapper.cpp
        ../utils/include/CStringCleaner.cpp)

target_link_libraries(Client CLogger)
target_link_libraries(Client Sockets)
