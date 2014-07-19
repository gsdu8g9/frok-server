QT -= core gui
CONFIG -= qt

TARGET = FaceDetectionApp
TEMPLATE = app

DESTDIR = ./bin
OBJECTS_DIR = ./obj

OBJECTS_DIR = $$OBJECTS_DIR/$$TARGET

DEFINES +=

DEPENDPATH += ../FaceCommonLib/

INCLUDEPATH += ../FaceCommonLib/

QMAKE_CXXFLAGS +=   -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas
QMAKE_CFLAGS_DEBUG +=     -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas

HEADERS +=          \
    FaceServer.h    \
    FaceAgentConnector.h

SOURCES +=          \
    main.cpp        \
    FaceServer.cpp  \
    FaceAgentConnector.cpp
