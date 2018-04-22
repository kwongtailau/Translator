#-------------------------------------------------
#
# Project created by QtCreator 2017-11-03T14:19:12
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Translator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    Func_TranslateFromDatabase.cpp \
    Window_Main.cpp \
    Func_TranslateFromNet.cpp \
    Widget_TranslateSentences.cpp \
    Widget_TranslateWords.cpp \
    Widget_About.cpp

HEADERS += \
    Func_TranslateFromDatabase.h \
    Func_TranslateFromNet.h \
    Window_Main.h \
    Widget_TranslateSentences.h \
    Widget_TranslateWords.h \
    Widget_About.h

RESOURCES += \
    res.qrc
