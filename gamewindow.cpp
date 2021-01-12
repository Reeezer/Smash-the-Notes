#include "gamewindow.h"
#include <QDebug>
#include <QFontDatabase>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    _game = new Game();
    _player = new Character();
    
    if (!loadRessources(_game))
        qDebug() << "Failed to load ressources";
    
    _gameView = new GameView(_game, _player, this);
    addWidget(_gameView);

    setFixedSize(1000,600);
    setWindowTitle("Smash The Notes");

    _gameView->resize(this->width(), this->height());

    _endScreen = new EndScreen(_game, _player, this);
    addWidget(_endScreen);
    _endScreen->resize(this->width(), this->height());

    setCurrentWidget(_gameView);
    _gameView->initialize();

    //Connect
    QObject::connect(_gameView, &GameView::gameFinished, this, &GameWindow::displayEndScreen);
    QObject::connect(_endScreen, &EndScreen::restartGame, this, &GameWindow::displayGame);

}

GameWindow::~GameWindow()
{
    delete _game;
    delete _player;
}

void GameWindow::displayGame()
{
    setCurrentWidget(_gameView);
    _gameView->initialize();
}

void GameWindow::displayEndScreen()
{
    setCurrentWidget(_endScreen);
    _endScreen->initialize();
}
