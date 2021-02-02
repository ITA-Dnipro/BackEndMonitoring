cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
endif(MSVC)

set(UTILS_SRC_DIR ${CMAKE_SOURCE_DIR}/utils/include)
set(THIRD_PARTY_DIR ${CMAKE_SOURCE_DIR}/3rdParty/include)

if (UNIX)
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/LinuxUtils.cpp)
else()
    set(PLATFORM_SPECIFIC_UTILS ${UTILS_SRC_DIR}/WindowsUtils.cpp)
endif(UNIX)

add_subdirectory(CLogger)
add_subdirectory(Sockets)
add_subdirectory(Client)
add_subdirectory(Server)
