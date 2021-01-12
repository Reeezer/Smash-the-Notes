#include "gamewindow.h"
#include <QDebug>
#include <QFontDatabase>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setFixedSize(1000,600);
    setWindowTitle("Smash The Notes");

    _game = new Game();
    _player = new Character();
    
    if (!loadRessources(_game))
        qDebug() << "Failed to load ressources";
    
    _gameView = new GameView(_game, _player, this);
    addWidget(_gameView);
    _gameView->resize(this->width(), this->height());

    _endScreen = new EndScreen(_game, _player, this);
    addWidget(_endScreen);
    _endScreen->resize(this->width(), this->height());

    //Connect
    QObject::connect(_gameView, &GameView::gameFinished, this, &GameWindow::displayEndScreen);
    QObject::connect(_endScreen, &EndScreen::restartGame, this, &GameWindow::restartGame);

    setCurrentWidget(_gameView);
    _gameView->newGame();
}

GameWindow::~GameWindow()
{
    delete _game;
    delete _player;
}

void GameWindow::restartGame()
{
    setCurrentWidget(_gameView);
    _gameView->initialize();
}

void GameWindow::displayGame()
{
    setCurrentWidget(_gameView);
    _gameView->newGame();
}

void GameWindow::displayEndScreen()
{
    setCurrentWidget(_endScreen);
    _endScreen->initialize();
}
