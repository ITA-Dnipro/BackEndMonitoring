#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

find_path(LIBUUID_INCLUDE_DIR uuid.h PATH_SUFFIXES uuid)
find_library(LIBUUID_LIBRARY libuuid.a)

set(GUID_SRC_DIR ${CMAKE_SOURCE_DIR}/Guid/src)
set(GUID_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Guid/include)

include_directories(
        ${GUID_INCLUDE_DIR}
        ${LIBUUID_INCLUDE_DIR}
)

add_library(Guid ${GUID_SRC_DIR}/guid.cpp)

target_link_libraries(Guid ${LIBUUID_LIBRARY})
