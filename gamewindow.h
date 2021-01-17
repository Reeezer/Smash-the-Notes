#pragma once

#include <QStackedWidget>

#include "GameItems/character.h"
#include "gameview.h"
#include "mainsettings.h"
#include "controlsettings.h"
#include "splashscreen.h"
#include "endscreen.h"
#include "mainmenu.h"

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
//    void displaySongDetails();
    void displaySettings();
//    void displaySplashScreen();
    void displayControlSettings();

private:
    Game *_game;
    Character *_player;
    GameView *_gameView;
    EndScreen *_endScreen;
    MainMenu *_mainMenu;
    MainSettings *_mainSettings;
    ControlSettings *_controlSettings;
    SplashScreen *_splashScreen;

};

