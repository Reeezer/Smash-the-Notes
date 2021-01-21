#ifndef CONTROLSETTINGS_H
#define CONTROLSETTINGS_H

#include <QWidget>

class QPushButton;
class KeyBindButton;

#include "gamedata.h"

//TODO : VALEURS PAR DEFAUT
class ControlSettings : public QWidget
{
    Q_OBJECT

public:
    ControlSettings(GameData *game, QWidget *parent = nullptr);

signals:
    void displayMainSettings();

protected:
    void changeKeyBinding();

private:
    GameData *_game;

    KeyBindButton *_topNote1;
    KeyBindButton *_topNote2;
    KeyBindButton *_bottomNote1;
    KeyBindButton *_bottomNote2;
    KeyBindButton *_pauseButton;
    KeyBindButton *_resetButton;
    QPushButton *_returnButton;
};

#endif // CONTROLSETTINGS_H
