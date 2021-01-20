#include "mainmenu.h"
#include "dirutils.h"
#include "songitem.h"

MainMenu::MainMenu(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
{
    //Widgets
    songnameLabel = new QLabel(tr("Music: "), this);
    rankLabel = new QLabel(tr("Rank: "), this);
    highscoreLabel = new QLabel(tr("Highscore: "), this);

    startButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/right.png"), tr("Play"), this);
    detailsButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/barsHorizontal.png"), tr("Details"), this);
    settingsButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/wrench.png"), tr("Settings"), this);

    songsList = new QListWidget(this);
    musicPreview = new QMediaPlayer(this);

    //Widgets configuration
    startButton->setDisabled(true);
    detailsButton->setDisabled(true);
    initializeSongList(songsList);
    startButton->setIconSize(QSize(40, 40));
    detailsButton->setIconSize(QSize(40, 40));
    settingsButton->setIconSize(QSize(40, 40));

    //Layouts
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(detailsButton);
    buttons->addWidget(settingsButton);

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(songnameLabel);
    left->addWidget(rankLabel);
    left->addWidget(highscoreLabel);
    left->addStretch();
    left->addLayout(buttons);
    left->addWidget(startButton);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addWidget(songsList);
    this->setLayout(main);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainMenu { background-image: url(\":/img/Background2.png\"); } QListWidget { background-color: rgba(0, 0, 0, 0.2); }");

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

    /* normalement il devrait toujours y avoir un Song * associé, mais plutôt que de crash à cause d'une segfault on
     * on affiche un message d'erreur via qDebug(). De son côté l'utilisateur ne verra aucune différence */
    if (Song *song = getSelectedSong()) {
        songnameLabel->setText("Music: " + song->getArtist() + " - " + song->getTitle());

        if (song->getPlayCount() > 0) {
            switch(song->getRank()) {
            case SSS:
                rankLabel->setText("Rank: S++");
                break;
            case SS:
                rankLabel->setText("Rank: S+");
                break;
            case S:
                rankLabel->setText("Rank: S");
                break;
            case A:
                rankLabel->setText("Rank: A");
                break;
            case B:
                rankLabel->setText("Rank: B");
                break;
            case C:
                rankLabel->setText("Rank: C");
                break;
            case D:
                rankLabel->setText("Rank: D");
                break;
            }

            if (song->getHighscore() > 0)
                highscoreLabel->setText("Highscore: " + QString::number(song->getHighscore()));
            else
                highscoreLabel->setText(("Highscore: map not yet played"));
        } else {
            rankLabel->setText("Rank: unplayed");
            highscoreLabel->setText("Highscore: map not yet played");
        }
    } else {
        qDebug() << "uh oh, somehow adaptToSelectedSong() in'" __FILE__ "' got called, but didn't have a valid song associated, that should not happen";
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
