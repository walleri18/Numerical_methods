#-------------------------------------------------
#
# Project created by QtCreator 2016-10-12T07:41:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = TaskFive
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    SolutionApproximation.cpp \
    aboutqcustomplots.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    SolutionApproximation.h \
    aboutqcustomplots.h \
    qcustomplot.h

FORMS    += mainwindow.ui \
    aboutqcustomplots.ui

RESOURCES += \
    myresourse.qrc
