cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

find_program(NUGET_EXE NAMES nuget)
if(NOT NUGET_EXE)
    message("NUGET.EXE not found.")
    message(FATAL_ERROR "Please install this executable, and run CMake again.")
endif()

exec_program(${NUGET_EXE}
        ARGS install "gmock" -Version 1.10.0 -ExcludeVersion -OutputDirectory ${CMAKE_SOURCE_DIR}/packages)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # Using the modern MSVC preprocessor.
    # It is necessary for the correct work of the CLogger's macros.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
endif()

set(UTILS_SRC_DIR ${CMAKE_SOURCE_DIR}/utils/include)
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/3rdParty/include)

# Project uses platform-dependent utilities
# So we have to divide these modules
if (UNIX)
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/LinuxUtils.cpp)
    set(GMOCK_FOLDER gmock)
else()
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/WindowsUtils.cpp)
    set(GMOCK_FOLDER gmock.1.10.0)
endif()

# Add support for multithreading using the POSIX threads library
if(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

set(TEST_LIB_SRC_DIR ${CMAKE_SOURCE_DIR}/packages/${GMOCK_FOLDER}/lib/native/src)
set(TEST_LIB_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/packages/${GMOCK_FOLDER}/lib/native/include)

set(GTEST_SRC_DIR ${TEST_LIB_SRC_DIR}/gtest)
set(GMOCK_SRC_DIR ${TEST_LIB_SRC_DIR}/gmock)

set(GTEST_INCLUDE_DIR ${TEST_LIB_INCLUDE_DIR}/gtest)
set(GMOCK_INCLUDE_DIR ${TEST_LIB_INCLUDE_DIR}/gmock)

# We have to find unique CMakeLists.txt at these directories
add_subdirectory(CLogger)
add_subdirectory(Sockets)
add_subdirectory(Client/BackEndMonitoringClient)
add_subdirectory(Client/BackEndMonitoringClientCLI)
add_subdirectory(Client/BackEndMonitoringClientTests)
add_subdirectory(Server/BackEndMonitoringServer)
add_subdirectory(Server/BackEndMonitoringServerTests)
add_subdirectory(UtilsTests)
