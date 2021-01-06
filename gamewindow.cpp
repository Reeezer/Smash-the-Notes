#include "gamewindow.h"
#include <QDebug>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setWindowTitle("Smash The Notes");
    Game *game = new Game();

    GameView *gameView = new GameView(game, this);
    addWidget(gameView);

    MainSettings *mainSettings = new MainSettings(game, this);
    addWidget(mainSettings);

    ControlSettings *controlSettings = new ControlSettings(game, this);
    addWidget(controlSettings);

    setCurrentWidget(controlSettings);

    resize(800,400);


}

GameWindow::~GameWindow()
{
}

