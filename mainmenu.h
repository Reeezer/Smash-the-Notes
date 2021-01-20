#pragma once

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QMediaPlayer>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "gameview.h"
#include "song.h"
#include "game.h"

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(Game *game, QWidget *parent = nullptr);

    Song * getSelectedSong();

public slots:
    void adaptToSelectedSong();
    void adaptToPreselection();

private:
    Game *_game;

    QLabel *_songnameLabel;
    QLabel *_rankLabel;
    QLabel *_highscoreLabel;

    QPushButton *_startButton;
    QPushButton *_detailsButton;
    QPushButton *_settingsButton;

    QListWidget *_songsList;
    QMediaPlayer *_musicPreview;

    static void initializeSongList(QListWidget*);

signals:
    void displaySongDetails();
    void displayMainSettings();
    void displayGameView();
};

