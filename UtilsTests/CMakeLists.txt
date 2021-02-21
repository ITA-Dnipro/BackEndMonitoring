cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

link_directories(${CMAKE_BINARY_DIR}/CLogger)

include_directories(${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
        ${CMAKE_SOURCE_DIR}/CLogger/include
        ${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
        ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include
        ${CMAKE_SOURCE_DIR}/3rdParty/include
        ${CMAKE_SOURCE_DIR}/utils/include
        ${CMAKE_SOURCE_DIR}/packages/gmock.1.10.0/lib/native/include)

set(UTILS_TESTS_SRC_DIR ${CMAKE_SOURCE_DIR}/UtilsTests/src)

add_executable(UtilsTests
        ${TEST_SRC}
        ${THIRD_PARTY_DIR}/pugixml.cpp
        ${UTILS_SRC_DIR}/Utils.cpp
        ${UTILS_SRC_DIR}/CStringCleaner.cpp
        ${UTILS_SRC_DIR}/StrToNumWrapper.cpp
        ${UTILS_SRC_DIR}/CNumericTypesParser.cpp
        ${UTILS_SRC_DIR}/CReadFileWrapper.cpp
        ${UTILS_SRC_DIR}/CDataReader.cpp
        ${UTILS_SRC_DIR}/CXMLDataReader.cpp
        ${UTILS_SRC_DIR}/CHDDInfoSettings.cpp
        ${UTILS_SRC_DIR}/CProcessesInfoSettings.cpp
        ${UTILS_SRC_DIR}/CThreadPoolSettings.cpp
        ${UTILS_SRC_DIR}/CComunicationSettings.cpp
        ${UTILS_SRC_DIR}/CServerSettings.cpp
        ${UTILS_SRC_DIR}/CSettings.cpp
        ${UTILS_SRC_DIR}/CTimeSettings.cpp
        ${UTILS_SRC_DIR}/CLoggingSettings.cpp
        ${UTILS_SRC_DIR}/CEvent.cpp
        ${UTILS_SRC_DIR}/CThreadPool.cpp
        ${UTILS_SRC_DIR}/CJSONFormatter.cpp
        ${UTILS_SRC_DIR}/CJSONFormatSaver.cpp
        ${UTILS_TESTS_SRC_DIR}/Main.cpp
        ${UTILS_TESTS_SRC_DIR}/CNumericTypesParserTest.cpp
        ${UTILS_TESTS_SRC_DIR}/CStringCleanerTest.cpp
        ${UTILS_TESTS_SRC_DIR}/CStrToNumWrapperTest.cpp
        ${UTILS_TESTS_SRC_DIR}/CXMLDataReaderTest.cpp)

target_link_libraries(UtilsTests CLogger)
