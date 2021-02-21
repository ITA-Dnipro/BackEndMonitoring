cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # Using the modern MSVC preprocessor.
    # It is necessary for the correct work of the CLogger's macros.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif()

set(UTILS_SRC_DIR ${CMAKE_SOURCE_DIR}/utils/include)
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/3rdParty/include)

set(TEST_LIB_SRC_DIR ${CMAKE_SOURCE_DIR}/packages/gmock.1.10.0/lib/native/src)
set(TEST_SRC ${TEST_LIB_SRC_DIR}/gmock/gmock-all.cc ${TEST_LIB_SRC_DIR}/gtest/gtest-all.cc)

# Project uses platform-dependent utilities
# So we have to divide these modules
if (UNIX)
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/LinuxUtils.cpp)
else()
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/WindowsUtils.cpp)
endif()

# We have to find unique CMakeLists.txt at these directories
add_subdirectory(CLogger)
add_subdirectory(Sockets)
add_subdirectory(Client/BackEndMonitoringClient)
add_subdirectory(Client/BackEndMonitoringClientTests)
add_subdirectory(Server/BackEndMonitoringServer)
add_subdirectory(Server/BackEndMonitoringServerTests)
add_subdirectory(UtilsTests)
