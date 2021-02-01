cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

			
include_directories(${CMAKE_SOURCE_DIR}/CLogger/include
        ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
        ${CMAKE_SOURCE_DIR}/3rdParty/include
        ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
        ${CMAKE_SOURCE_DIR}/Sockets/BackEndMonitoringSockets/include
        ${CMAKE_SOURCE_DIR}/utils/include)

add_subdirectory(CLogger)
add_subdirectory(Sockets)
add_subdirectory(Client)
add_subdirectory(Server)
