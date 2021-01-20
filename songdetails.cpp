#include "songdetails.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SongDetails::SongDetails(QWidget *parent)
    : QWidget(parent)
{
    titleLabel = new QLabel;
    highscoreLabel = new QLabel;
    rankLabel = new QLabel;
    highscoreList = new QListWidget;
    returnButton = new QPushButton(QIcon(":/img/Icons/PNG/White/2x/arrowLeft.png"), "", this);

    returnButton->setIconSize(QSize(40, 40));

    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addWidget(titleLabel);
    leftLayout->addWidget(highscoreLabel);
    leftLayout->addWidget(rankLabel);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addLayout(leftLayout);
    bottomLayout->addWidget(highscoreList);

    QHBoxLayout *spacerLayout = new QHBoxLayout;
    spacerLayout->addWidget(returnButton, 1);
    spacerLayout->addStretch(9);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(spacerLayout);
    mainLayout->addLayout(bottomLayout);

    connect(returnButton, &QPushButton::clicked, this, &SongDetails::displayMainMenu);
}

void SongDetails::setSongDetails(Song *song)
{
    highscoreList->clear();
    titleLabel->setText(song->getArtist() + " - " + song->getTitle());
    highscoreLabel->setText("Highscore : " + QString::number(song->getHighscore()));
    highscoreList->addItems(song->getHighscoreList());

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
}
