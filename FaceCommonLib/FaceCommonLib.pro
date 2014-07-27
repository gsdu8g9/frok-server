QT -= core gui
CONFIG -= qt

TARGET = FaceCommonLib
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ./bin
OBJECTS_DIR = ./obj

OBJECTS_DIR = $$OBJECTS_DIR/$$TARGET

DEFINES +=  \
            NETWORK_SYSTEM_DEBUG_PRINT_ENABLED

QMAKE_CXXFLAGS +=   -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas
QMAKE_CFLAGS_DEBUG +=     -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas

INCLUDEPATH +=

HEADERS +=                  \
    json.h                  \
    commonThread.h          \
    io.h                    \
    faceCommonLib.h \
    trace.h

SOURCES +=                  \
    json.cpp                \
    commonThread.cpp        \
    io.cpp                  \
    faceCommonLib.cpp
