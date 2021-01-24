#include "songdetails.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

SongDetails::SongDetails(QWidget *parent)
    : QWidget(parent)
{
    _titleLabel = new QLabel;
    _highscoreLabel = new QLabel;
    _rankLabel = new QLabel;
    _highscoreList = new QListWidget;
    _returnButton = new QPushButton(QIcon(":/img/Icons/arrowLeft.png"), "", this);

    _returnButton->setIconSize(QSize(40, 40));

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(_titleLabel);
    leftLayout->addWidget(_highscoreLabel);
    leftLayout->addWidget(_rankLabel);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addLayout(leftLayout);
    bottomLayout->addWidget(_highscoreList);

    QHBoxLayout *spacerLayout = new QHBoxLayout;
    spacerLayout->addWidget(_returnButton, 1);
    spacerLayout->addStretch(9);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(spacerLayout);
    mainLayout->addLayout(bottomLayout);

    setAttribute(Qt::WA_StyledBackground);
    setStyleSheet("SongDetails { background-image: url(\":/img/Background2.png\"); } QListWidget { background-color: rgba(0, 0, 0, 0.2); }");

    connect(_returnButton, &QPushButton::clicked, this, &SongDetails::displayMainMenu);
}

void SongDetails::setSongDetails(Song *song)
{
    _highscoreList->clear();
    _titleLabel->setText(song->getArtist() + " - " + song->getTitle());
    _highscoreLabel->setText("Highscore : " + QString::number(song->getHighscore()));
    _highscoreList->addItems(song->getHighscoreList());

    switch (song->getRank())
    {
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
}
