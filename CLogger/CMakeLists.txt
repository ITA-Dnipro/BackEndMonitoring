cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

include_directories(${CMAKE_SOURCE_DIR}
		${CMAKE_SOURCE_DIR}/CLogger/include
		${CMAKE_SOURCE_DIR}/utils/include
		${CMAKE_SOURCE_DIR}/3rdParty/include)

set(CLOGGER_SRC_DIR ${CMAKE_SOURCE_DIR}/CLogger/src)

add_library(CLogger
		${CLOGGER_SRC_DIR}/CLogBuilder/CLogBuilder.cpp
		${CLOGGER_SRC_DIR}/CLogger/CLogger.cpp
		${CLOGGER_SRC_DIR}/ELogConfig/ELogConfig.cpp
		${CLOGGER_SRC_DIR}/ELogFlush/ELogFlush.cpp
		${CLOGGER_SRC_DIR}/ELogLevel/ELogLevel.cpp)
