#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Smash The Notes");
    setFixedSize(1000, 600);

    Game *game = new Game();
    Character *player = new Character();

    gameView = new GameView(game, player, this);
    addWidget(gameView);

    endScreen = new EndScreen(game, player, this);
    addWidget(endScreen);

    setCurrentWidget(gameView);

    //Connect
    connect(gameView, &GameView::gameFinished, this, &GameWindow::displayEndScreen);
}

GameWindow::~GameWindow()
{
}

void GameWindow::displayEndScreen()
{
    setCurrentWidget(endScreen);
}
