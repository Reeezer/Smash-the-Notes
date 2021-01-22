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
    gamedata.cpp \
    gameitems/note.cpp \
    gameitems/character.cpp\
    controlsettings.cpp \
    animatable.cpp \
    dirutils.cpp \
    endscreen.cpp \
    fileutils.cpp \
    gameview.cpp \
    gamewindow.cpp \
    keybindbutton.cpp \
    keydialog.cpp \
    main.cpp \
    mainmenu.cpp \
    mainsettings.cpp \
    song.cpp \
    songdetails.cpp \
    songitem.cpp \
    splashscreen.cpp \

HEADERS += \
    controlsettings.h \
    gamedata.h \
    gameitems/note.h \
    gameitems/character.h\
    animatable.h \
    dirutils.h \
    endscreen.h \
    fileutils.h \
    gameview.h \
    gamewindow.h \
    keybindbutton.h \
    keydialog.h \
    mainmenu.h \
    mainsettings.h \
    rank.h \
    song.h \
    songdetails.h \
    songitem.h \
    splashscreen.h \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
