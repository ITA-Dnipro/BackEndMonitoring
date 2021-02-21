cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

include_directories(${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
        ${CMAKE_SOURCE_DIR}/CLogger/include
        ${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
        ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
        ${CMAKE_SOURCE_DIR}/3rdParty/include
        ${CMAKE_SOURCE_DIR}/utils/include
        ${GTEST_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${TEST_LIB_INCLUDE_DIR}
        ${GTEST_SRC_DIR}
        ${GMOCK_SRC_DIR})

set(CLIENT_TESTS_SRC_DIR ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClientTests/src)

add_executable(ClientTests
        ${GTEST_SRC_DIR}/gtest-all.cc
        ${GMOCK_SRC_DIR}/gmock-all.cc
        ${CLIENT_TESTS_SRC_DIR}/Main.cpp)
