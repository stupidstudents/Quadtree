#-------------------------------------------------
#
# Project created by QtCreator 2018-05-11T15:22:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quadgui
TEMPLATE = app

TRANSLATIONS = languages/lang_en.ts languages/lang_ru.ts

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
