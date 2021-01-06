#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QListWidget;
class QMediaPlayer;

#include "game.h"

class MainMenu : public QWidget
{
public:
    MainMenu(Game *game, QWidget *parent = nullptr);

private:
    Game *game;

    QLabel *songnameLabel;
    QLabel *difficultyLabel;
    QLabel *highscoreLabel;

    QPushButton *startButton;
    QPushButton *detailsButton;
    QPushButton *settingsButton;

    QListWidget *songList;
    QMediaPlayer *musicPreview;
};

