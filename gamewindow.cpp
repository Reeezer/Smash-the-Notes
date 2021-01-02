#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Smash The Notes");
    setFixedSize(1000, 600);

    Game *game = new Game();
    Character *player = new Character();

    GameView *gameView = new GameView(game, player, this);
    addWidget(gameView);

    EndScreen *endScreen = new EndScreen(game, player, this);
    addWidget(endScreen);

    setCurrentWidget(endScreen);
}

GameWindow::~GameWindow()
{
}
