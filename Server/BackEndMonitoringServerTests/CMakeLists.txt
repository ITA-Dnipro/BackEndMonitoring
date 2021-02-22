#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

#------------------------------ SRC/INCLUDE DIRS' VARS --------------------------------#

set(SERVER_TESTS_SRC_DIR ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServerTests/src)

#------------------------------------ INCLUDE DIRS -------------------------------------#

include_directories(${CMAKE_SOURCE_DIR}
        ${NLOHMANN_JSON_INCLUDE_DIR}
        ${TEST_LIB_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${GTEST_SRC_DIR}
        ${GMOCK_SRC_DIR}
        ${UTILS_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
        ${CMAKE_SOURCE_DIR}/CLogger/include)

#--------------------------------- EXECUTE CONFIGS -------------------------------------#

add_executable(ServerTests
        ${GTEST_SRC_DIR}/gtest-all.cc
        ${GMOCK_SRC_DIR}/gmock-all.cc
        ${SERVER_TESTS_SRC_DIR}/Main.cpp)

#----------------------------------- TARGET LIBS ---------------------------------------#

target_link_libraries(ServerTests CLogger)
