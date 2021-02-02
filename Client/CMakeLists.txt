cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /Zc:preprocessor")

link_directories(${CMAKE_BINARY_DIR}/CLogger)
link_directories(.)
link_directories(${CMAKE_BINARY_DIR}/Sockets)

include_directories(${CMAKE_SOURCE_DIR}
        include
        ${CMAKE_SOURCE_DIR}/3rdParty/include
        ${CMAKE_SOURCE_DIR}/utils/include)

add_executable(Client BackEndMonitoringClient/src/BackEndMonitoringClient.cpp
        BackEndMonitoringClient/src/CClient.cpp
        BackEndMonitoringClient/src/CClientView.cpp
        ${CMAKE_SOURCE_DIR}/utils/include/WindowsUtils.cpp
        ../utils/include/CReadFileWrapper.cpp
        ../utils/include/CNumericTypesParser.cpp
        ../utils/include/Utils.cpp
        ../utils/include/StrToNumWrapper.cpp
        ../utils/include/CStringCleaner.cpp)

target_link_libraries(Client CLogger)
target_link_libraries(Client Sockets)
