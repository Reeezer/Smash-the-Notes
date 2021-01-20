#pragma once

#include <QWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QSlider>
#include <QLineEdit>
#include <QFormLayout>
#include <QObject>
#include <QVBoxLayout>

#include "pathwidget.h"
#include "game.h"

class MainSettings : public QWidget
{
    Q_OBJECT

public:
    MainSettings(Game *game, QWidget *parent = nullptr);

signals:
    void displayMainMenu();
    void displayControlSettings();

protected:
    void validateAndUpdateSongDirectory();
    void openModalFileExplorer();

    void updateDelay();
    void updateVolume();

private:
    Game *_game;

    QSpinBox *_delaySpinBox;
    QPushButton *_inputButton;
    QPushButton *_mapPathButton;
    QSlider *_volumeSlider;
    PathWidget *_pathWidget;
    QPushButton *_returnButton;
};

