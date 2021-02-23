#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

set(GUID_SRC_DIR ${CMAKE_SOURCE_DIR}/Guid/src)
set(GUID_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Guid/include)

include_directories(${GUID_INCLUDE_DIR})

add_library(Guid ${GUID_SRC_DIR}/guid.cpp)