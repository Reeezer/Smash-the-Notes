#ifndef MAINSETTINGS_H
#define MAINSETTINGS_H

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>

#include "game.h"

class MainSettings : public QWidget
{
public:
    MainSettings(Game *game, QWidget *parent = nullptr);

private:
    Game *game;

    QSpinBox *delaySpinBox;
    QPushButton *inputButton;
    QSlider *volumeSlider;
    QLineEdit *mapPathText;
    QPushButton *mapPathButton;
};

#endif // MAINSETTINGS_H
