QT -= core gui
CONFIG -= qt

TARGET = FaceDetectionApp
TEMPLATE = app

DESTDIR = ./bin
OBJECTS_DIR = ./obj

OBJECTS_DIR = $$OBJECTS_DIR/$$TARGET

DEFINES +=
INCLUDEPATH += ../../FaceDetectionLib
INCLUDEPATH += ../../FaceDetectionLib

INCLUDEPATH +=                                          \
    /opt/opencv-2.4.9/install/include/opencv/           \
    /opt/opencv-2.4.9/install/include/opencv2/          \

QMAKE_CXXFLAGS +=   -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas
QMAKE_CFLAGS_DEBUG +=     -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas

HEADERS +=      \
    stdafx.h

SOURCES +=      \
    main.cpp