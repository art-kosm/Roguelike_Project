TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    map.cpp \
    actor.cpp \
    dungeon.cpp \
    gameController.cpp \
    tile.cpp \
    terrain.cpp \
    entrance.cpp

include(deployment.pri)
qtcAddDeployment()

QMAKE_CXXFLAGS += -std=c++11


win32: LIBS += -L$$PWD/../libs/pdc34dllw/ -lpdcurses

INCLUDEPATH += $$PWD/../libs/pdc34dllw
DEPENDPATH += $$PWD/../libs/pdc34dllw

HEADERS += \
    generalConstants.h \
    map.h \
    actor.h \
    dungeon.h \
    gameController.h \
    tile.h \
    terrain.h \
    entrance.h
