#include "mainmenu.h"

MainMenu::MainMenu(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
{
    //Widgets
    songnameLabel = new QLabel("Musique", this);
    difficultyLabel = new QLabel("Difficulté", this);
    highscoreLabel = new QLabel("Highscore", this);

    startButton = new QPushButton("Play", this); //TODO : icon
    detailsButton = new QPushButton("Détails", this); //TODO : icon
    settingsButton = new QPushButton("Options", this); //TODO : icon

    songsList = new QListWidget(this);
    musicPreview = new QMediaPlayer(this); //TODO : flags

    //Widgets configuration
    startButton->setDisabled(true);
    detailsButton->setDisabled(true);
    initializeQListWidget(songsList);

    //Layouts
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(detailsButton);
    buttons->addWidget(settingsButton);

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(songnameLabel);
    left->addWidget(difficultyLabel);
    left->addWidget(highscoreLabel);
    left->addLayout(buttons);
    left->addWidget(startButton);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addWidget(songsList);
    this->setLayout(main);

    //Connections
    connect(startButton, &QPushButton::clicked, this, &MainMenu::playSelectedSong);
    connect(songsList, &QListWidget::itemDoubleClicked, this, &MainMenu::playSelectedSong);
    connect(detailsButton, &QPushButton::clicked, this, &MainMenu::openSelectedSongDetails);
    connect(settingsButton, &QPushButton::clicked, this, &MainMenu::openSettingsMenu);
    connect(songsList, &QListWidget::itemClicked, this, &MainMenu::adaptToSelectedSong);
    connect(songsList, &QListWidget::itemEntered, this, &MainMenu::adaptToPreselection);
}

void MainMenu::initializeQListWidget(QListWidget* songsList)
{
//    QList<Song*> list = getSongList();
//    for(int i = 0; i < list.length(); i++)
//    {
//        songsList->addItem(QString(list.at(i)->artist + " - " list.at(i)->title));
//    }
}

void MainMenu::playSelectedSong()
{
    emit gameViewCall();
}

void MainMenu::openSelectedSongDetails()
{
    emit songDetailsCall();
}

void MainMenu::openSettingsMenu()
{
    emit mainSettingsCall();
}

void MainMenu::adaptToSelectedSong()
{

}

void MainMenu::adaptToPreselection()
{

}
