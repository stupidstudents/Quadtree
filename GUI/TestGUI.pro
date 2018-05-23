#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T15:22:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestGUI
TEMPLATE = app


SOURCES += main.cpp\
        paint.cpp \
    paintscene.cpp \
    quadtree.cpp \
    customlabel.cpp \
    readfile.cpp

HEADERS  += paint.h \
    paintscene.h \
    quadtree.h \
    customlabel.h \
    readfile.h

FORMS    += paint.ui

unix:!mac {

 LIBS += —Wl,—rpath=\\\$$ORIGIN/../lib

} 

target.path = /usr/share/QuadGUI/bin

target.files = QuadGUI qt.conf

INSTALLS += target 

data.path = /usr/share/QuadGUI/lib

data.files = lib/*

INSTALLS += data
