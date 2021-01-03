#include "endscreen.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QDebug>

EndScreen::EndScreen(Game *game, Character *player, QWidget *parent)
    : QWidget(parent), game(game), player(player)
{
    //Custom font
    QFont Foo("Foo", 18, QFont::Normal);
    QFont BigFoo("Foo", 50, QFont::Normal);
    QFont MiddleFoo("Foo", 30, QFont::Normal);

    //Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

        //Left
    QVBoxLayout *leftLayout = new QVBoxLayout;
    mainLayout->addLayout(leftLayout);
    leftLayout->setAlignment(Qt::AlignCenter);

            //Title left
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setAlignment(Qt::AlignCenter);
    leftLayout->addLayout(titleLayout);
    leftLayout->addStretch();

    QLabel *title = new QLabel("Victory");
    titleLayout->addWidget(title);
    title->setFont(BigFoo);

            //Results left
    QGridLayout *labelLayout = new QGridLayout;
    leftLayout->addStretch();
    leftLayout->addLayout(labelLayout);

    scoreLabel = new QLabel();
    highScoreLabel = new QLabel();
    perfectLabel = new QLabel();
    greatLabel = new QLabel();
    missLabel = new QLabel();
    passLabel = new QLabel();

    labelLayout->addWidget(scoreLabel, 0 , 0);
    labelLayout->addWidget(highScoreLabel, 0, 1);
    labelLayout->addWidget(perfectLabel, 1, 0);
    labelLayout->addWidget(greatLabel, 1, 1);
    labelLayout->addWidget(missLabel, 2, 0);
    labelLayout->addWidget(passLabel, 2, 1);

    scoreLabel->setFont(Foo);
    highScoreLabel->setFont(Foo);
    perfectLabel->setFont(Foo);
    greatLabel->setFont(Foo);
    missLabel->setFont(Foo);
    passLabel->setFont(Foo);

            //Accuracy Left
    QVBoxLayout *accuracyLayout = new QVBoxLayout;
    leftLayout->addLayout(accuracyLayout);
    accuracyLabel = new QLabel();
    noteLabel = new QLabel();

    accuracyLabel->setFont(Foo);
    noteLabel->setFont(MiddleFoo);
    accuracyLabel->setAlignment(Qt::AlignCenter);
    noteLabel->setAlignment(Qt::AlignCenter);

    accuracyLayout->addWidget(accuracyLabel);
    accuracyLayout->addWidget(noteLabel);

            //Button left
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    leftLayout->addStretch();
    leftLayout->addLayout(buttonLayout);
    leftLayout->addStretch();

    QPushButton *menuButton = new QPushButton("Menu");
    QPushButton *restartButton = new QPushButton("Restart");
    buttonLayout->addStretch();
    buttonLayout->addWidget(menuButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(restartButton);
    buttonLayout->addStretch();

        //Right
    //EN ATTENDANT
    QPixmap pix(":/img/Background/Fever.png");

    QLabel *pixmap = new QLabel;
    pixmap->setPixmap(pix);

    mainLayout->addWidget(pixmap);

    //Connect
    connect(restartButton, &QPushButton::clicked, this, &EndScreen::restartGame);
}

EndScreen::~EndScreen()
{
}


void EndScreen::initialize()
{
    scoreLabel->setText("Score : " + QString::asprintf("%d", player->getScore()));
    highScoreLabel->setText("High score : " + QString::asprintf("%d", 0));
    perfectLabel->setText("Perfect : " + QString::asprintf("%d", player->getPerfect()));
    greatLabel->setText("Great : " + QString::asprintf("%d", player->getGreat()));
    missLabel->setText("Miss : " + QString::asprintf("%d", player->getMiss()));
    passLabel->setText("Pass : " + QString::asprintf("%d", player->getPass()));
    accuracyLabel->setText("Accuracy : " + QString::asprintf("%.1f", player->getAccuracy()) + "%");

    if(player->getAccuracy() > 99)
        noteLabel->setText("S++");
    else if(player->getAccuracy() > 95)
        noteLabel->setText("S+");
    else if(player->getAccuracy() > 90)
        noteLabel->setText("S");
    else if(player->getAccuracy() > 80)
        noteLabel->setText("A");
    else if(player->getAccuracy() > 70)
        noteLabel->setText("B");
    else if(player->getAccuracy() > 50)
        noteLabel->setText("C");
    else
        noteLabel->setText("D");
}
