#-------------------------------------------------
#
# Project created by QtCreator 2015-04-09T09:23:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FFT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ideal_low_pass.cpp \
    ideal_high_pass.cpp \
    ideal_emphasis.cpp

HEADERS  += mainwindow.h

CONFIG += qtimagelib \
          fftw3

LIBS += -L$$PWD/lib -lfftw3
