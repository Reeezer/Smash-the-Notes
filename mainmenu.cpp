#include "mainmenu.h"
#include "dirutils.h"
#include "songitem.h"

MainMenu::MainMenu(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
{
    //Widgets
    songnameLabel = new QLabel(tr("Music: "), this);
    difficultyLabel = new QLabel(tr("Difficulty: "), this);
    highscoreLabel = new QLabel(tr("Highscore: "), this);

    startButton = new QPushButton(QIcon(":/img/Icons/PNG/Black/1x/forward.png"), tr("Play"), this);
    detailsButton = new QPushButton(QIcon(":/img/Icons/PNG/Black/1x/barsHorizontal.png"), tr("Details"), this);
    settingsButton = new QPushButton(QIcon(":/img/Icons/PNG/Black/1x/wrench.png"), tr("Settings"), this);

    songsList = new QListWidget(this);
    musicPreview = new QMediaPlayer(this);

    //Widgets configuration
    startButton->setDisabled(true);
    detailsButton->setDisabled(true);
    initializeSongList(songsList);

    //Layouts
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(detailsButton);
    buttons->addWidget(settingsButton);

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(songnameLabel);
    left->addWidget(difficultyLabel);
    left->addWidget(highscoreLabel);
    left->addStretch();
    left->addLayout(buttons);
    left->addWidget(startButton);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addWidget(songsList);
    this->setLayout(main);

    //Connections
    connect(startButton, &QPushButton::clicked, this, &MainMenu::displayGameView);
    connect(songsList, &QListWidget::itemDoubleClicked, this, &MainMenu::displayGameView);
    connect(detailsButton, &QPushButton::clicked, this, &MainMenu::displaySongDetails);
    connect(settingsButton, &QPushButton::clicked, this, &MainMenu::displayMainSettings);
    connect(songsList, &QListWidget::itemClicked, this, &MainMenu::adaptToSelectedSong);
    connect(songsList, &QListWidget::itemEntered, this, &MainMenu::adaptToPreselection);
}

void MainMenu::initializeSongList(QListWidget* songsList)
{
    QList<Song*> list;
    getSongList("C:\\Users\\ethan.millet\\Desktop\\Niveau 2\\P2\\git\\songdir", &list);
    for(Song *song : list)
    {
        songsList->addItem(new SongItem(song));
    }
}

void MainMenu::adaptToSelectedSong()
{
    /* une fois qu'une musique a été sélectionnée on peut activer les boutons de façon permanente */
    startButton->setEnabled(true);
    detailsButton->setEnabled(true);

    if (Song *song = getSelectedSong()) {
        songnameLabel->setText("Music: " + song->getArtist() + " - " + song->getTitle());
    }
}

void MainMenu::adaptToPreselection()
{

}

Song * MainMenu::getSelectedSong()
{
    SongItem *selectedItem = (SongItem*) songsList->currentItem();

    if (selectedItem)
        return selectedItem->getSong();
    else
        return nullptr;
}
