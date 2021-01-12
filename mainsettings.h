#pragma once

#include <QWidget>

class QSpinBox;
class QPushButton;
class QSlider;
class QLineEdit;

#include "game.h"

class MainSettings : public QWidget
{
public:
    MainSettings(Game *game, QWidget *parent = nullptr);

private:
    Game *game;

    QSpinBox *delaySpinBox;
    QPushButton *inputButton;
    QPushButton *mapPathButton;
    QSlider *volumeSlider;
    QLineEdit *mapPathText;
};

