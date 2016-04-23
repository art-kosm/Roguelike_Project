TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    map.cpp \
    mapElement.cpp \
    actor.cpp \
    terrainElement.cpp \
    dungeon.cpp

include(deployment.pri)
qtcAddDeployment()


win32: LIBS += -L$$PWD/../libs/pdc34dllw/ -lpdcurses

INCLUDEPATH += $$PWD/../libs/pdc34dllw
DEPENDPATH += $$PWD/../libs/pdc34dllw

HEADERS += \
    generalConstants.h \
    map.h \
    mapElement.h \
    actor.h \
    terrainElement.h \
    dungeon.h
