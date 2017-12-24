QT += core
QT += network
CONFIG += c++11

TARGET = pokemon
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    pokemon.cpp \
    bulbasaur.cpp

HEADERS += \
    pokemon.h \
    type.h \
    all_head.h \
    bulbasaur.h
