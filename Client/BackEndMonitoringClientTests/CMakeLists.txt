cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

include_directories(${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
        ${CMAKE_SOURCE_DIR}/CLogger/include
        ${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
        ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
        ${CMAKE_SOURCE_DIR}/3rdParty/include
        ${CMAKE_SOURCE_DIR}/utils/include
        ${CMAKE_SOURCE_DIR}/packages/gmock.1.10.0/lib/native/include)

set(CLIENT_TESTS_SRC_DIR ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClientTests/src)

add_executable(ClientTests
        ${TEST_SRC}
        ${CLIENT_TESTS_SRC_DIR}/Main.cpp)