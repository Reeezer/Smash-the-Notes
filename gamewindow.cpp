#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Smash The Notes");
    Game *game = new Game();
    GameView *gameView = new GameView(game, this);

    addWidget(gameView);
    setFixedSize(1000,600);
}

GameWindow::~GameWindow()
{
}

