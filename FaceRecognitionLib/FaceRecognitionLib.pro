QT -= core gui
CONFIG -= qt

TARGET = lib-common
TEMPLATE = lib
CONFIG += staticlib
DESTDIR = ./bin
OBJECTS_DIR = ./obj

OBJECTS_DIR = $$OBJECTS_DIR/$$TARGET

DEFINES +=  \
            TRACE_DEBUG

QMAKE_CXXFLAGS +=   -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas
QMAKE_CFLAGS_DEBUG +=     -Werror -Wall -Wno-unused-function -Wno-write-strings -Wno-unused-result -Wno-unknown-pragmas

DEPENDPATH += ../FrokLibCommon/

INCLUDEPATH += /opt/opencv-2.4.9/static/include/opencv/
INCLUDEPATH += /opt/opencv-2.4.9/static/include/opencv2/
INCLUDEPATH += /opt/opencv-2.4.9/static/include
INCLUDEPATH += ../FrokLibCommon/

HEADERS +=                  \
    FaceRecognizerAbstract.h \
    FaceModelAbstract.h \
    FaceRecognizerEigenfaces.h \
    FaceModelEigenfaces.h \
    FaceModelFisherfaces.h

SOURCES +=                  \
    FaceModelAbstract.cpp \
    FaceModelEigenfaces.cpp \
    FaceRecognizerEigenfaces.cpp \
    FaceRecognizerAbstract.cpp \
    FaceModelFisherfaces.cpp

