cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(CLogger)
add_subdirectory(Sockets)
add_subdirectory(Client)
add_subdirectory(Server)

include_directories(CLogger/include)
include_directories(Client/BackEndMonitoringClient)
include_directories(3rdParty/include)
include_directories(Server/BackEndMonitoringServer/include)
include_directories(Sockets/BackEndMonitoringSockets/include)
include_directories(utils/include)