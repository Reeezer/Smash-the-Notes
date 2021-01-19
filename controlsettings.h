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
    Game *game;

    QPushButton *topNote1;
    QPushButton *topNote2;
    QPushButton *bottomNote1;
    QPushButton *bottomNote2;
    QPushButton *pauseButton;
    QPushButton *resetButton;
    QPushButton *validationButton;
    QPushButton *returnButton;

signals:
    void displayMainSettings();
};

#endif // CONTROLSETTINGS_H
