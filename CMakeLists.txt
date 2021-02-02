cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:preprocessor")
endif(MSVC)

if (UNIX)
    set(UTILS ${CMAKE_SOURCE_DIR}/utils/include/LinuxUtils.cpp)
else()
    set(UTILS ${CMAKE_SOURCE_DIR}/utils/include/WindowsUtils.cpp)
endif(UNIX)

add_subdirectory(CLogger)
add_subdirectory(Sockets)
add_subdirectory(Client)
add_subdirectory(Server)
