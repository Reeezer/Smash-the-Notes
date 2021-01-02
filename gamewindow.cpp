#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Smash The Notes");
    setFixedSize(1000, 600);

    Game *game = new Game();

    GameView *gameView = new GameView(game, this);
    addWidget(gameView);

    EndScreen *splashScreen = new EndScreen(game, this);
    addWidget(splashScreen);
}

GameWindow::~GameWindow()
{
}
