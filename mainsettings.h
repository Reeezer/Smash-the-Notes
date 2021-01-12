#pragma once

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QFormLayout>
#include <QObject>

#include "pathwidget.h"
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
    PathWidget *pathWidget;

public slots:
    void setNewDelay();
    void displayControlSettings();
    void setNewVolume();
    void validateAndSetNewDirectory();
    void openModalFileExplorer();
};

