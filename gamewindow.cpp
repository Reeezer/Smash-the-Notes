#include "gamewindow.h"

#include <QDebug>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QStandardPaths>
#include <QDir>

GameWindow::GameWindow(QWidget *parent)
    : QStackedWidget(parent)
{
    setFixedSize(1000, 600);
    setWindowTitle("Smash The Notes");
    setWindowIcon(QIcon(":/img/Icons/musicOn.png"));

    _game = new GameData();
    _game->_dataBasePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    _game->_settingsPath = _game->_dataBasePath + "/settings.json";
    _game->_songdirPath = _game->_dataBasePath + "/songdir";

    qDebug() << "setting base path for maps and data to " << _game->_dataBasePath;
    _player = new Character();
    _mediaPlayer = new QMediaPlayer(this);

    if (!loadRessources(_game))
        qDebug() << "failed to load ressources";

    if (!loadSettingsFile(_game->_settingsPath, _game))
        qDebug() << "failed to read settings";

    _mediaPlayer->setVolume(_game->_volume);

    _gameView = new GameView(_game, _player, _mediaPlayer, this);
    addWidget(_gameView);
    _gameView->resize(this->width(), this->height());

    _mainMenu = new MainMenu(_game, _mediaPlayer, this);
    addWidget(_mainMenu);
    _mainMenu->resize(this->width(), this->height());

    _mainSettings = new MainSettings(_game, _mediaPlayer, this);
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

    _songDetails = new SongDetails(this);
    addWidget(_songDetails);
    _songDetails->resize(this->width(), this->height());

    //Connect
    connect(_gameView, &GameView::displayEndScreen, this, &GameWindow::displayEndScreen);
    connect(_gameView, &GameView::displayMainMenu, this, &GameWindow::displayMainMenu);
    connect(_endScreen, &EndScreen::restartGame, this, &GameWindow::restartGame);
    connect(_endScreen, &EndScreen::displayMainMenu, this, &GameWindow::displayMainMenu);
    connect(_mainSettings, &MainSettings::displayMainMenu, this, &GameWindow::displayMainMenu);
    connect(_mainSettings, &MainSettings::displayControlSettings, this, &GameWindow::displayControlSettings);
    connect(_mainMenu, &MainMenu::displayGameView, this, &GameWindow::displayGame);
    connect(_mainMenu, &MainMenu::displaySongDetails, this, &GameWindow::displaySongDetails);
    connect(_mainMenu, &MainMenu::displayMainSettings, this, &GameWindow::displaySettings);
    connect(_splashScreen, &SplashScreen::displayMainMenu, this, &GameWindow::displayMainMenu);
    connect(_controlSettings, &ControlSettings::displayMainSettings, this, &GameWindow::displaySettings);
    connect(_controlSettings, &ControlSettings::keyBindingsUpdated, _mainSettings, &MainSettings::saveSettings);
    connect(_songDetails, &SongDetails::displayMainMenu, this, &GameWindow::displayMainMenu);

    setCurrentWidget(_splashScreen);
}

GameWindow::~GameWindow()
{
    delete _game;
    delete _player;
}

void GameWindow::restartGame()
{
    qDebug() << "restarting game and switching to the game view";
    _gameView->restartGame();
    setCurrentWidget(_gameView);
    _gameView->setFocus();
}

void GameWindow::displayGame()
{
    Song *song = _mainMenu->getSelectedSong();
    qDebug() << "starting game with the map at '" + song->getPath() + "' and switching to the game view";

    if (song)
    {
        _gameView->newGame(song);
        setCurrentWidget(_gameView);
        _gameView->setFocus();
    }
    else
        qDebug() << "uh oh, somehow displayGame() got called in '" __FILE__ "' without any song selected in the main menu, that shouldn't happen, not starting the game";
}

void GameWindow::displayEndScreen()
{
    qDebug() << "switching to the endscreen view";
    _endScreen->initialize();
    setCurrentWidget(_endScreen);
}

void GameWindow::displayMainMenu()
{
    qDebug() << "displaying the main menu";

    /* mettre à jour le score en réaffichant le song actuel (pour quand on est sortis du jeu) */
    if (_mainMenu->getSelectedSong())
        _mainMenu->adaptToSelectedSong();
    setCurrentWidget(_mainMenu);
}

void GameWindow::displayControlSettings()
{
    qDebug() << "displaying the controls settings";
    setCurrentWidget(_controlSettings);
}

void GameWindow::displaySettings()
{
    qDebug() << "displaying the main settings";
    setCurrentWidget(_mainSettings);
}

void GameWindow::displaySongDetails()
{
    Song *song = _mainMenu->getSelectedSong();
    if (song)
    {
        qDebug() << "displaying the song details for the map '" + song->getPath() + "'";
        _songDetails->setSongDetails(song);
        setCurrentWidget(_songDetails);
    }
    else
        qDebug() << "uh oh, displaySongDetails() got called without a song selected, this shouldn't happen, not switching view";
}
