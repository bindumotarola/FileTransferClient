#-------------------------------------------------
#
# Project created by QtCreator 2013-08-30T09:59:02
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileTransferTest
TEMPLATE = app


SOURCES += main.cpp\
        filetransfer.cpp \
    sendfile.cpp \
    receivefile.cpp \
    addstudent.cpp \
    servercliant.cpp \
    removestudent.cpp

HEADERS  += filetransfer.h \
    sendfile.h \
    receivefile.h \
    addstudent.h \
    servercliant.h \
    removestudent.h

FORMS    += filetransfer.ui \
    sendfile.ui \
    receivefile.ui \
    addstudent.ui \
    removestudent.ui
