#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Smash The Notes");
    Game *game = new Game();
    GameView *gameView = new GameView(game, this);

    addWidget(gameView);
    resize(1200,800);
}

GameWindow::~GameWindow()
{
}

