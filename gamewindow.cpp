#include "gamewindow.h"
#include <QDebug>
#include <QFontDatabase>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    //Custom font
    QFontDatabase::addApplicationFont(":/font/foo.ttf");
    QFontDatabase::addApplicationFont(":/font/karen.otf");

    setWindowTitle("Smash The Notes");
    setFixedSize(1000, 600);

    Game *game = new Game();
    Character *player = new Character();

    gameView = new GameView(game, player, this);
    addWidget(gameView);
    gameView->resize(this->width(), this->height());

    endScreen = new EndScreen(game, player, this);
    addWidget(endScreen);
    endScreen->resize(this->width(), this->height());

    setCurrentWidget(gameView);
    gameView->initialize();

    //Connect
    connect(gameView, &GameView::gameFinished, this, &GameWindow::displayEndScreen);
    connect(endScreen, &EndScreen::restartGame, this, &GameWindow::displayGame);
}

GameWindow::~GameWindow()
{
}

void GameWindow::displayGame()
{
    setCurrentWidget(gameView);
    gameView->initialize();
}

void GameWindow::displayEndScreen()
{
    setCurrentWidget(endScreen);
    endScreen->initialize();
}
