#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

#------------------------------ SRC/INCLUDE DIRS' VARS --------------------------------#

set(CLOGGER_SRC_DIR ${CMAKE_SOURCE_DIR}/CLogger/src)

#------------------------------------ INCLUDE DIRS -------------------------------------#

include_directories(${CMAKE_SOURCE_DIR}
		${NLOHMANN_JSON_INCLUDE_DIR}
		${UTILS_INCLUDE_DIR}
		${CMAKE_SOURCE_DIR}/CLogger/include)

#------------------------------------ BUILD OPTIONS ------------------------------------#

# Comment if you want to build dynamic library
set(CLOG_STATIC_BUILD 1)

if (CLOG_STATIC_BUILD)
	set(CLOG_BUILD STATIC)
	# Set predefined macro to build static library
	set(CMAKE_CXX_COMPILER_PREDEFINES_COMMAND "${CMAKE_CXX_COMPILER_PREDEFINES_COMMAND} CLOG_STATIC_BUILD")
else()
	set(CLOG_BUILD SHARED)
endif()

#--------------------------------- EXECUTE CONFIGS -------------------------------------#

add_library(CLogger ${CLOG_BUILD}
		${CLOGGER_SRC_DIR}/CLogBuilder/CLogBuilder.cpp
		${CLOGGER_SRC_DIR}/CLogger/CLogger.cpp
		${CLOGGER_SRC_DIR}/ELogConfig/ELogConfig.cpp
		${CLOGGER_SRC_DIR}/ELogFlush/ELogFlush.cpp
		${CLOGGER_SRC_DIR}/ELogLevel/ELogLevel.cpp
		${CLOGGER_SRC_DIR}/CLoggerGlobal/GlobalLogger.cpp)
