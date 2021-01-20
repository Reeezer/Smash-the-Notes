#ifndef CONTROLSETTINGS_H
#define CONTROLSETTINGS_H

#include <QWidget>
#include <QPushButton>
#include <QFormLayout>

#include "game.h"

//TODO : VALEURS PAR DEFAUT
class ControlSettings : public QWidget
{
    Q_OBJECT
public:
    ControlSettings(Game *game, QWidget *parent = nullptr);

private:
    Game *_game;

    QPushButton *_topNote1;
    QPushButton *_topNote2;
    QPushButton *_bottomNote1;
    QPushButton *_bottomNote2;
    QPushButton *_pauseButton;
    QPushButton *_resetButton;
    QPushButton *_validationButton;
    QPushButton *_returnButton;

signals:
    void displayMainSettings();
};

#endif // CONTROLSETTINGS_H
