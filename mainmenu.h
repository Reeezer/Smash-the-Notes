#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QMediaPlayer>

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

#endif // MAINMENU_H
