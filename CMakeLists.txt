cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    # Using the modern MSVC preprocessor.
    # It is necessary for the correct work of the CLogger's macros.
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
endif(${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")

set(UTILS_SRC_DIR ${CMAKE_SOURCE_DIR}/utils/include)
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/3rdParty/include)

# Project uses platform-dependent utilities
# So we have to divide these modules
if (UNIX)
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/LinuxUtils.cpp)
else()
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/WindowsUtils.cpp)
endif(UNIX)

# We have to find unique CMakeLists.txt at these directories
add_subdirectory(CLogger)
add_subdirectory(Sockets)
add_subdirectory(Client)
add_subdirectory(Server)
