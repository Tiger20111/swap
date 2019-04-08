TARGET = Cam
TEMPLATE = app

QT += multimedia multimediawidgets


CONFIG += c++11

SOURCES += \
        main.cpp \
        cam.cpp \
    ball.cpp \
    myitem.cpp

HEADERS += \
        cam.h \
    ball.h \
    myitem.h

FORMS += \
        cam.ui

QT+=widgets
include(../../multimedia/shared/shared.pri)
