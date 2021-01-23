#include "mainmenu.h"
#include "dirutils.h"
#include "songitem.h"
#include "common.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QMediaPlayer>


MainMenu::MainMenu(GameData *game, QMediaPlayer *mediaPlayer, QWidget *parent)
    : QWidget(parent), _game(game), _musicPreview(mediaPlayer)
{
    //Widgets
    _songnameLabel = new QLabel(tr("Music: "), this);
    _rankLabel = new QLabel(tr("Rank: "), this);
    _highscoreLabel = new QLabel(tr("Highscore: "), this);

    _startButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/right.png"), tr("Play"), this);
    _detailsButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/barsHorizontal.png"), tr("Details"), this);
    _settingsButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/wrench.png"), tr("Settings"), this);

    _songsList = new QListWidget(this);

    //Widgets configuration
    _startButton->setDisabled(true);
    _detailsButton->setDisabled(true);
    initializeSongList(_songsList);
    _startButton->setIconSize(QSize(40, 40));
    _detailsButton->setIconSize(QSize(40, 40));
    _settingsButton->setIconSize(QSize(40, 40));

    //Layouts
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(_detailsButton);
    buttons->addWidget(_settingsButton);

    QVBoxLayout *left = new QVBoxLayout;
    left->addWidget(_songnameLabel);
    left->addWidget(_rankLabel);
    left->addWidget(_highscoreLabel);
    left->addStretch();
    left->addLayout(buttons);
    left->addWidget(_startButton);

    QHBoxLayout *main = new QHBoxLayout;
    main->addLayout(left);
    main->addWidget(_songsList);
    this->setLayout(main);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("MainMenu { background-image: url(\":/img/Background2.png\"); } QListWidget { background-color: rgba(0, 0, 0, 0.2); }");

    //Connections
    connect(_startButton, &QPushButton::clicked, this, &MainMenu::displayGameView);
    connect(_songsList, &QListWidget::itemDoubleClicked, this, &MainMenu::displayGameView);
    connect(_detailsButton, &QPushButton::clicked, this, &MainMenu::displaySongDetails);
    connect(_settingsButton, &QPushButton::clicked, this, &MainMenu::displayMainSettings);
    connect(_songsList, &QListWidget::itemClicked, this, &MainMenu::adaptToSelectedSong);
}

void MainMenu::initializeSongList(QListWidget* songsList)
{
    QList<Song*> list;
    getSongList(BASE_PATH "\\songdir", &list);
    for(Song *song : list)
    {
        songsList->addItem(new SongItem(song));
    }
}

void MainMenu::adaptToSelectedSong()
{
    /* une fois qu'une musique a été sélectionnée on peut activer les boutons de façon permanente */
    _startButton->setEnabled(true);
    _detailsButton->setEnabled(true);

    /* normalement il devrait toujours y avoir un Song * associé, mais plutôt que de crash à cause d'une segfault on
     * on affiche un message d'erreur via qDebug(). De son côté l'utilisateur ne verra aucune différence */
    if (Song *song = getSelectedSong()) {
        qDebug() << "displaying details for map at '" + song->getPath() + "'";

        QMediaContent media = QUrl::fromLocalFile(song->getAudioFilePath());
        if (_musicPreview->media() != media) {
            _musicPreview->setMedia(media);
            _musicPreview->play();
        }

        _songnameLabel->setText("Music: " + song->getArtist() + " - " + song->getTitle());

        if (song->getPlayCount() > 0) {
            switch(song->getRank()) {
            case SSS:
                _rankLabel->setText("Rank: S++");
                break;
            case SS:
                _rankLabel->setText("Rank: S+");
                break;
            case S:
                _rankLabel->setText("Rank: S");
                break;
            case A:
                _rankLabel->setText("Rank: A");
                break;
            case B:
                _rankLabel->setText("Rank: B");
                break;
            case C:
                _rankLabel->setText("Rank: C");
                break;
            case D:
                _rankLabel->setText("Rank: D");
                break;
            }

            if (song->getHighscore() > 0)
                _highscoreLabel->setText("Highscore: " + QString::number(song->getHighscore()));
            else
                _highscoreLabel->setText(("Highscore: map not yet played"));
        } else {
            _rankLabel->setText("Rank: unplayed");
            _highscoreLabel->setText("Highscore: map not yet played");
        }
    } else {
        qDebug() << "uh oh, somehow adaptToSelectedSong() in'" __FILE__ "' got called, but didn't have a valid song associated, that should not happen";
    }
}

Song * MainMenu::getSelectedSong()
{
    SongItem *selectedItem = (SongItem*) _songsList->currentItem();

    if (selectedItem)
        return selectedItem->getSong();
    else
        return nullptr;
}
