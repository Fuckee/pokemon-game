#-------------------------------------------------
#
# Project created by QtCreator 2016-12-05T14:36:07
#
#-------------------------------------------------

QT       += core gui
QT       +=network
QT       +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = myserver
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    server.cpp \
    socket.cpp \
    add_dialog.cpp \
    checkdialog.cpp \
    deletedialog.cpp \
    sqldialog.cpp \
    pokemon/bulbasaur.cpp \
    pokemon/pokemon.cpp \
    addpokemon.cpp \
    serveradd.cpp \
    addserverpoke.cpp \
    player.cpp

HEADERS  += dialog.h \
    server.h \
    socket.h \
    add_dialog.h \
    checkdialog.h \
    deletedialog.h \
    sqldialog.h \
    pokemon/all_head.h \
    pokemon/bulbasaur.h \
    pokemon/pokemon.h \
    pokemon/type.h \
    addpokemon.h \
    serveradd.h \
    addserverpoke.h \
    player.h

FORMS    += dialog.ui \
    add_dialog.ui \
    checkdialog.ui \
    deletedialog.ui \
    sqldialog.ui \
    addpokemon.ui \
    serveradd.ui \
    addserverpoke.ui

SUBDIRS += \
    pokemon/pokemon.pro
