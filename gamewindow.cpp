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

    _mainMenu = new MainMenu(_game, this);
    addWidget(_mainMenu);
    _mainMenu->resize(this->width(), this->height());

    _mainSettings = new MainSettings(_game, this);
    addWidget(_mainSettings);
    _mainSettings->resize(this->width(), this->height());

    _controlSettings = new ControlSettings(_game, this);
    addWidget(_controlSettings);
    _controlSettings->resize(this->width(), this->height());

    _splashScreen = new SplashScreen(this);
    addWidget(_splashScreen);
    _splashScreen->resize(this->width(), this->height());

    _endScreen = new EndScreen(_game, _player, this);
    addWidget(_endScreen);
    _endScreen->resize(this->width(), this->height());

    //Connect
    QObject::connect(_gameView, &GameView::gameFinished, this, &GameWindow::displayEndScreen);
    QObject::connect(_endScreen, &EndScreen::restartGame, this, &GameWindow::restartGame);
    QObject::connect(_mainSettings, &MainSettings::mainMenuCall, this, &GameWindow::displayMainMenu);
    QObject::connect(_mainSettings, &MainSettings::controlSettingsCall, this, &GameWindow::displayControlSettings);

    _gameView->newGame();
    setCurrentWidget(_mainSettings);
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

void GameWindow::displayMainMenu()
{
    setCurrentWidget(_mainMenu);
}

void GameWindow::displayControlSettings()
{
    setCurrentWidget(_controlSettings);
}
