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
    entrance.cpp \
    fieldOfView.cpp \
    AI.cpp \
    aggressiveAI.cpp \
    playerAI.cpp \
    cowardlyAI.cpp \
    UI.cpp \
    item.cpp \
    weapon.cpp \
    armor.cpp \
    inventory.cpp \
    town.cpp \
    citizenAI.cpp \
    potion.cpp \
    traderAI.cpp \
    gradalis.cpp

QMAKE_CXXFLAGS += -std=c++11

HEADERS += \
    generalConstants.h \
    map.h \
    actor.h \
    dungeon.h \
    gameController.h \
    tile.h \
    terrain.h \
    entrance.h \
    fieldOfView.h \
    AI.h \
    aggressiveAI.h \
    playerAI.h \
    cowardlyAI.h \
    UI.h \
    item.h \
    weapon.h \
    armor.h \
    inventory.h \
    cellularAutomataGenerator.h \
    town.h \
    citizenAI.h \
    potion.h \
    traderAI.h \
    gradalis.h

unix|win32: LIBS += -L$$PWD/../libs/pdc34dllw/ -lpdcurses

INCLUDEPATH += $$PWD/../libs/pdc34dllw
DEPENDPATH += $$PWD/../libs/pdc34dllw
