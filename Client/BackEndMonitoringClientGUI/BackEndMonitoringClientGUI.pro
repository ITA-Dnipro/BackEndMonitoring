QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../../
INCLUDEPATH += $$PWD/../../Client/BackEndMonitoringClient/include
INCLUDEPATH += $$PWD/../../CLogger/include
INCLUDEPATH += $$PWD/../../BackEndMonitoringSockets/include
INCLUDEPATH += $$PWD/../../Server/BackEndMonitoringServer/include
INCLUDEPATH += $$PWD/../../utils/include
INCLUDEPATH += $$PWD/../../3rdParty/include
INCLUDEPATH += $$PWD/../../packages/nlohmann.json.3.9.1/build/native/include

HEADERS += \
    ../../utils/include/stdafx.h \
    CConnectionDialog.h \
    CConnectionErrorDialog.h \
    CDrivesGraph.h \
    CDrivesTab.h \
    CDrivesTable.h \
    CMainWindow.h \
    CProcessesGraph.h \
    CProcessesTab.h \
    CProcessesTable.h \
    CRequestDialog.h \
    qcustomplot.h

SOURCES += \
    CConnectionErrorDialog.cpp \
    stadafx.cpp \
    $$PWD/../../utils/include/Utils.cpp \
    $$PWD/../../utils/include/CRequestFrame.cpp \
    ../BackEndMonitoringClient/src/CClientController.cpp \
    CConnectionDialog.cpp \
    CDrivesGraph.cpp \
    CDrivesTab.cpp \
    CDrivesTable.cpp \
    CProcessesGraph.cpp \
    CProcessesTab.cpp \
    CProcessesTable.cpp \
    CRequestDialog.cpp \
    main.cpp \
    CMainWindow.cpp \
    qcustomplot.cpp


FORMS += \
    CConnectionDialog.ui \
    CConnectionErrorDialog.ui \
    CMainWindow.ui \
    CRequestDialog.ui

RC_ICONS = monitor.ico

win32: {
    QMAKE_CXXFLAGS += /Zc:preprocessor
    DEFINES -= UNICODE
    DEFINES -= _UNICODE

    QMAKE_CXXFLAGS_RELEASE += -MD
    QMAKE_CFLAGS_RELEASE += -MD

    QMAKE_CXXFLAGS_DEBUG += -MDd
    QMAKE_CFLAGS_DEBUG += -MDd

    CONFIG(debug, debug|release){
        win32: LIBS += -L$$PWD/../../packages/Client/Debug/x64/ -lBackEndMonitoringClient
        INCLUDEPATH += $$PWD/../BackEndMonitoringClient/include
        DEPENDPATH += $$PWD/../BackEndMonitoringClient/include
        win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Client/Debug/x64/BackEndMonitoringClient.lib
        else:win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Client/Debug/x64/libBackEndMonitoringClient.a


        win32: LIBS += -L$$PWD/../../packages/Sockets/Debug/x64/ -lBackEndMonitoringSockets
        INCLUDEPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include
        DEPENDPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include
        win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Sockets/Debug/x64/BackEndMonitoringSockets.lib
        else:win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Sockets/Debug/x64/libBackEndMonitoringSockets.a


        win32: LIBS += -L$$PWD/../../packages/CLogger/Debug/x64/ -lCLogger
        INCLUDEPATH += $$PWD/../../CLogger/include
        DEPENDPATH += $$PWD/../../CLogger/include


        win32: LIBS += -L$$PWD/../../packages/Guid/Debug/x64/ -lGuid

        INCLUDEPATH += $$PWD/../../Guid/include
        DEPENDPATH += $$PWD/../../Guid/include

        win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Guid/Debug/x64/Guid.lib
        else:win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Guid/Debug/x64/libGuid.a
    }

    CONFIG(release, debug|release)
    {
        win32: LIBS += -L$$PWD/../../packages/Client/Release/x64/ -lBackEndMonitoringClient
        INCLUDEPATH += $$PWD/../BackEndMonitoringClient/include
        DEPENDPATH += $$PWD/../BackEndMonitoringClient/include
        win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Client/Release/x64/BackEndMonitoringClient.lib
        else:win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Client/Release/x64/libBackEndMonitoringClient.a


        win32: LIBS += -L$$PWD/../../packages/Sockets/Release/x64/ -lBackEndMonitoringSockets
        INCLUDEPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include
        DEPENDPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include
        win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Sockets/Release/x64/BackEndMonitoringSockets.lib
        else:win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Sockets/Release/x64/libBackEndMonitoringSockets.a


        win32: LIBS += -L$$PWD/../../packages/CLogger/Release/x64/ -lCLogger
        INCLUDEPATH += $$PWD/../../CLogger/include
        DEPENDPATH += $$PWD/../../CLogger/include


        win32: LIBS += -L$$PWD/../../packages/Guid/Release/x64/ -lGuid
        INCLUDEPATH += $$PWD/../../Guid/include
        DEPENDPATH += $$PWD/../../Guid/include
        win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Guid/Release/x64/Guid.lib
        else:win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Guid/Release/x64/libGuid.a
    }
}

unix: !macx: {
    unix:!macx: LIBS += -L$$PWD/../../CLogger/ -lCLogger
    INCLUDEPATH += $$PWD/../../CLogger
    DEPENDPATH += $$PWD/../../CLogger
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../CLogger/libCLogger.a


    unix:!macx: LIBS += -L$$PWD/../../Guid/ -lGuid
    INCLUDEPATH += $$PWD/../../Guid/include
    DEPENDPATH += $$PWD/../../Guid/include
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../Guid/libGuid.a

    unix:!macx: LIBS += -L$$PWD/../../Sockets/BackEndMonitoringSockets/ -lSockets
    INCLUDEPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include
    DEPENDPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include
    unix:!macx: PRE_TARGETDEPS += $$PWD/../../Sockets/BackEndMonitoringSockets/libSockets.a

    unix:!macx: LIBS += -L$$PWD/../BackEndMonitoringClient/ -lClient
    INCLUDEPATH += $$PWD/../BackEndMonitoringClient/include
    DEPENDPATH += $$PWD/../BackEndMonitoringClient/include
    unix:!macx: PRE_TARGETDEPS += $$PWD/../BackEndMonitoringClient/libClient.a

    unix:!macx: LIBS += -luuid
}

