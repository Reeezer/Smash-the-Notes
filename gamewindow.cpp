#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    if (!loadRessources(&_game))
        qDebug() << "Failed to load ressources";

    GameView *gameView = new GameView(&_game, this);

    addWidget(gameView);
    setFixedSize(1000,600);
    setWindowTitle("Smash The Notes");
}

GameWindow::~GameWindow()
{
}

