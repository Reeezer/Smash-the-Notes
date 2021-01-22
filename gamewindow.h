#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QStackedWidget>

class QMediaPlayer;

#include "gameitems/character.h"
#include "gameview.h"
#include "mainsettings.h"
#include "controlsettings.h"
#include "splashscreen.h"
#include "endscreen.h"
#include "mainmenu.h"
#include "songdetails.h"

class GameWindow : public QStackedWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

public slots:
    void displayEndScreen();
    void displayGame();
    void restartGame();
    void displayMainMenu();
    void displaySongDetails();
    void displaySettings();
    void displayControlSettings();

private:
    GameData *_game;
    Character *_player;
    GameView *_gameView;
    EndScreen *_endScreen;
    MainMenu *_mainMenu;
    MainSettings *_mainSettings;
    ControlSettings *_controlSettings;
    SplashScreen *_splashScreen;
    SongDetails *_songDetails;

    QMediaPlayer *_mediaPlayer;
};

#endif // GAMEWINDOW_H
