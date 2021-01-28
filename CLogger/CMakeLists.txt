cmake_minimum_required(VERSION 3.17)
project(CLogger)

set(CMAKE_CXX_STANDARD 17)

add_compile_definitions(CLOG_NONCLIENT_BUILD)

include_directories(include)

add_library(Static src/CLogBuilder/CLogBuilder.cpp
        src/CLogger/CLogger.cpp
        src/ELogConfig/ELogConfig.cpp
        src/ELogFlush/ELogFlush.cpp
        src/ELogLevel/ELogLevel.cpp
        src/DllMain.cpp)

add_library(Dynamic SHARED src/CLogBuilder/CLogBuilder.cpp
        src/CLogger/CLogger.cpp
        src/ELogConfig/ELogConfig.cpp
        src/ELogFlush/ELogFlush.cpp
        src/ELogLevel/ELogLevel.cpp
        src/DllMain.cpp)