#-------------------------------------------------
#
# Project created by QtCreator 2016-09-21T19:12:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TaskFour
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    Interpolation.cpp \
    aboutme.cpp \
    aboutqcustomplots.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    Interpolation.h \
    aboutme.h \
    aboutqcustomplots.h

FORMS    += mainwindow.ui \
    aboutme.ui \
    aboutqcustomplots.ui

RESOURCES += \
    myresourse.qrc
