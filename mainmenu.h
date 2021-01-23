#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>

class QLabel;
class QPushButton;
class QListWidget;
class QMediaPlayer;

#include "gameview.h"
#include "song.h"
#include "gamedata.h"

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    MainMenu(GameData *game, QMediaPlayer *, QWidget *parent = nullptr);

    Song * getSelectedSong();

public slots:
    void adaptToSelectedSong();

signals:
    void displaySongDetails();
    void displayMainSettings();
    void displayGameView();

private:
    void initializeSongList(QListWidget*);

    GameData *_game;

    QLabel *_songnameLabel;
    QLabel *_rankLabel;
    QLabel *_highscoreLabel;

    QPushButton *_startButton;
    QPushButton *_detailsButton;
    QPushButton *_settingsButton;

    QListWidget *_songsList;
    QMediaPlayer *_musicPreview;
};

#endif // MAINMENU_H
