cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_SOURCE_DIR}
        include
        ${CMAKE_SOURCE_DIR}/3rdParty/include
        ${CMAKE_SOURCE_DIR}/utils/include)

#add_library(StaticCLogger src/CLogBuilder/CLogBuilder.cpp
#        src/CLogger/CLogger.cpp
#        src/ELogConfig/ELogConfig.cpp
#        src/ELogFlush/ELogFlush.cpp
#        src/ELogLevel/ELogLevel.cpp
#        src/DllMain.cpp)

add_library(CLogger src/CLogBuilder/CLogBuilder.cpp
        src/CLogger/CLogger.cpp
        src/ELogConfig/ELogConfig.cpp
        src/ELogFlush/ELogFlush.cpp
        src/ELogLevel/ELogLevel.cpp
        src/DllMain.cpp)
