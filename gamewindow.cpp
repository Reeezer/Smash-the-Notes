#include "gamewindow.h"
#include "mainmenu.h"
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

    setFixedSize(1000,600);
    setWindowTitle("Smash The Notes");

    MainMenu *mainMenu = new MainMenu(_game, this);
    addWidget(mainMenu);
    
    MainSettings *mainSettings = new MainSettings(_game, this);
    addWidget(mainSettings);

    ControlSettings *controlSettings = new ControlSettings(_game, this);
    addWidget(controlSettings);
    
    SplashScreen *splashScreen = new SplashScreen(this);
    addWidget(splashScreen);
    
    _gameView->resize(this->width(), this->height());

    _endScreen = new EndScreen(_game, _player, this);
    addWidget(_endScreen);
    _endScreen->resize(this->width(), this->height());

    //Connect
    QObject::connect(_gameView, &GameView::gameFinished, this, &GameWindow::displayEndScreen);
    QObject::connect(_endScreen, &EndScreen::restartGame, this, &GameWindow::restartGame);

    _gameView->newGame();
    setCurrentWidget(_gameView);
}

GameWindow::~GameWindow()
{
    delete _game;
    delete _player;
}

void GameWindow::restartGame()
{
    _gameView->initialize();
    setCurrentWidget(_gameView);
}

void GameWindow::displayGame()
{
    _gameView->newGame();
    setCurrentWidget(_gameView);
}

void GameWindow::displayEndScreen()
{
    _endScreen->initialize();
    setCurrentWidget(_endScreen);
}
