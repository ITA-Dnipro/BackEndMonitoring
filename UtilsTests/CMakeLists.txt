#----------------------------------- CMAKE SETTINGS ------------------------------------#

cmake_minimum_required(VERSION 3.17)
project(BackEndMonitoring)

#------------------------------ SRC/INCLUDE DIRS' VARS --------------------------------#

set(UTILS_TESTS_SRC_DIR ${CMAKE_SOURCE_DIR}/UtilsTests/src)

#------------------------------------ INCLUDE DIRS -------------------------------------#

include_directories(${CMAKE_SOURCE_DIR}
        ${PUGIXML_INCLUDE_DIR}
        ${NLOHMANN_JSON_INCLUDE_DIR}
        ${GTEST_INCLUDE_DIR}
        ${GMOCK_INCLUDE_DIR}
        ${TEST_LIB_INCLUDE_DIR}
        ${GTEST_SRC_DIR}
        ${GMOCK_SRC_DIR}
        ${UTILS_INCLUDE_DIR}
        ${CMAKE_SOURCE_DIR}/Client/BackEndMonitoringClient/include
        ${CMAKE_SOURCE_DIR}/CLogger/include
        ${CMAKE_SOURCE_DIR}/BackEndMonitoringSockets/include
        ${CMAKE_SOURCE_DIR}/Server/BackEndMonitoringServer/include)

#--------------------------------- EXECUTE CONFIGS -------------------------------------#

add_executable(UtilsTests
        ${GTEST_SRC_DIR}/gtest-all.cc
        ${GMOCK_SRC_DIR}/gmock-all.cc
        ${PUGIXML_SRC_DIR}/pugixml.cpp
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

#----------------------------------- TARGET LIBS ---------------------------------------#

target_link_libraries(UtilsTests CLogger)
