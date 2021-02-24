#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

#-------------------------------- LANGUAGE SETTINGS ------------------------------------#

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

#------------------------------ NUGET PACKAGES DOWNLOAD --------------------------------#

if (${CMAKE_SYSTEM_NAME} STREQUAL Linux OR ${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    set(NUGET_INSTALL_STR "Installation for Debian-like systems: sudo apt install nuget")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL Windows)
    set(NUGET_INSTALL_STR "Installation for Windows-like systems: check site https:////www.nuget.org//downloads")
endif()

find_program(NUGET_EXE NAMES nuget)

if(NOT NUGET_EXE)
    message(FATAL_ERROR
            "NuGet hasn't been found. "
            "Please, install this executable, and run CMake again\n"
            "${NUGET_INSTALL_STR}\n")
endif()

set(NUGET_PACKAGES_DIR ${CMAKE_SOURCE_DIR}/packages)

set(GMOCK_FOLDER gmock.1.10.0)
set(PUGIXML_FOLDER pugixml.1.11.0)
set(NLOHMANN_JSON_FOLDER nlohmann.json.3.9.1)

exec_program("${NUGET_EXE} install gmock -Version 1.10.0 -OutputDirectory \"${NUGET_PACKAGES_DIR}\"")
exec_program("${NUGET_EXE} install pugixml -Version 1.11.0 -OutputDirectory \"${NUGET_PACKAGES_DIR}\"")
exec_program("${NUGET_EXE} install nlohmann.json -Version 3.9.1 -OutputDirectory \"${NUGET_PACKAGES_DIR}\"")

#------------------------------ SRC/INCLUDE DIRS' VARS --------------------------------#

set(TEST_LIB_SRC_DIR "${NUGET_PACKAGES_DIR}/${GMOCK_FOLDER}/lib/native/src")
set(TEST_LIB_INCLUDE_DIR "${NUGET_PACKAGES_DIR}/${GMOCK_FOLDER}/lib/native/include")

set(GTEST_SRC_DIR "${TEST_LIB_SRC_DIR}/gtest")
set(GTEST_INCLUDE_DIR "${TEST_LIB_INCLUDE_DIR}/gtest")

set(GMOCK_SRC_DIR "${TEST_LIB_SRC_DIR}/gmock")
set(GMOCK_INCLUDE_DIR "${TEST_LIB_INCLUDE_DIR}/gmock")

set(PUGIXML_SRC_DIR "${NUGET_PACKAGES_DIR}/${PUGIXML_FOLDER}/build/native/include")
set(PUGIXML_INCLUDE_DIR "${NUGET_PACKAGES_DIR}/${PUGIXML_FOLDER}/build/native/include")

set(NLOHMANN_JSON_SRC_DIR "${NUGET_PACKAGES_DIR}/${NLOHMANN_JSON_FOLDER}/build/native/include/nlohmann")
set(NLOHMANN_JSON_INCLUDE_DIR "${NUGET_PACKAGES_DIR}/${NLOHMANN_JSON_FOLDER}/build/native/include")

set(UTILS_SRC_DIR "${CMAKE_SOURCE_DIR}/utils/include")
set(UTILS_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/utils/include")

#-------------------------------- COMPILER SPECIFIC SETTINGS ---------------------------#

if (${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    # Using the modern MSVC preprocessor. It is necessary for the correct work of the CLogger's macros.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
elseif(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w")
    # Add support for multithreading using the POSIX threads library
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
endif()

#-------------------------------- OS SPECIFIC SETTINGS ---------------------------------#

# Project uses platform-dependent utilities
# So we have to divide these modules
if (${CMAKE_SYSTEM_NAME} STREQUAL Linux OR ${CMAKE_SYSTEM_NAME} STREQUAL Darwin)
    set(PLATFORM_SPECIFIC_UTILS "${UTILS_SRC_DIR}/LinuxUtils.cpp")
    add_definitions(-DGUID_LIBUUID)
else(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    set(PLATFORM_SPECIFIC_UTILS "${UTILS_SRC_DIR}/WindowsUtils.cpp")
    add_definitions(-DGUID_WINDOWS)
endif()

#----------------------------------- CMAKE SUBDIRS -------------------------------------#

add_subdirectory(CLogger)
add_subdirectory(Sockets/BackEndMonitoringSockets)
add_subdirectory(Guid)
add_subdirectory(Client/BackEndMonitoringClient)
add_subdirectory(Client/BackEndMonitoringClientCLI)
add_subdirectory(Client/BackEndMonitoringClientTests)
add_subdirectory(Server/BackEndMonitoringServer)
add_subdirectory(Server/BackEndMonitoringServerTests)
add_subdirectory(UtilsTests)
