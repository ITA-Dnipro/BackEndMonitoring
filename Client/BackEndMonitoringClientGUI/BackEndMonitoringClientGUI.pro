QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++17
QMAKE_CXXFLAGS += /Zc:preprocessor
DEFINES -= UNICODE
DEFINES -= _UNICODE

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$PWD/../../

SOURCES += \
    ../../utils/include/Utils.cpp \
    CConnectionDialog.cpp \
    CDrivesTab.cpp \
    CDrivesTable.cpp \
    CProcessesTab.cpp \
    CProcessesTable.cpp \
    CRequestDialog.cpp \
    main.cpp \
    CMainWindow.cpp \
    qcustomplot.cpp

HEADERS += \
    CConnectionDialog.h \
    CDrivesTab.h \
    CDrivesTable.h \
    CMainWindow.h \
    CProcessesTab.h \
    CProcessesTable.h \
    CRequestDialog.h \
    ERequestDataType.h \
    qcustomplot.h

FORMS += \
    CConnectionDialog.ui \
    CMainWindow.ui \
    CRequestDialog.ui

unix|win32: LIBS += -L$$PWD/../../packages/Client/Debug/x64/ -lBackEndMonitoringClient

INCLUDEPATH += $$PWD/../BackEndMonitoringClient/include
DEPENDPATH += $$PWD/../BackEndMonitoringClient/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Client/Debug/x64/BackEndMonitoringClient.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Client/Debug/x64/libBackEndMonitoringClient.a

unix|win32: LIBS += -L$$PWD/../../packages/Sockets/Debug/x64/ -lBackEndMonitoringSockets

INCLUDEPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include
DEPENDPATH += $$PWD/../../Sockets/BackEndMonitoringSockets/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Sockets/Debug/x64/BackEndMonitoringSockets.lib
else:unix|win32-g++: PRE_TARGETDEPS += $$PWD/../../packages/Sockets/Debug/x64/libBackEndMonitoringSockets.a

unix|win32: LIBS += -L$$PWD/../../packages/CLogger/Debug/x64/ -lCLogger

INCLUDEPATH += $$PWD/../../CLogger/include
DEPENDPATH += $$PWD/../../CLogger/include
