TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tcpclient.cpp \
    udpclient.cpp \
    client.cpp

HEADERS += \
    tcpclient.h \
    udpclient.h \
    client.h

