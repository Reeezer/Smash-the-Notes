QT       += core gui
QT += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

CONFIG += c++11
CONFIG += resources_big
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GameItems/note.cpp \
    GameItems/character.cpp\
    animatable.cpp \
    endscreen.cpp \
    game.cpp \
    gameview.cpp \
    gamewindow.cpp \
    main.cpp \
    mainmenu.cpp \
    mainsettings.cpp \
    songdetails.cpp \
    songfile.cpp \
    splashscreen.cpp \

HEADERS += \
    GameItems/note.h \
    GameItems/character.h\
    animatable.h \
    endscreen.h \
    game.h \
    gameview.h \
    gamewindow.h \
    mainmenu.h \
    mainsettings.h \
    songdetails.h \
    songfile.h \
    splashscreen.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
