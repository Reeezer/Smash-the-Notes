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

    QLabel *scoreLabel = new QLabel("Score : " + QString::asprintf("%d", player->getScore()));
    QLabel *highScoreLabel = new QLabel("High score : " + QString::asprintf("%d", 0));
    QLabel *perfectLabel = new QLabel("Perfect : " + QString::asprintf("%d", player->getPerfect()));
    QLabel *greatLabel = new QLabel("Great : " + QString::asprintf("%d", player->getGreat()));
    QLabel *missLabel = new QLabel("Miss : " + QString::asprintf("%d", player->getMiss()));
    QLabel *passLabel = new QLabel("Pass : " + QString::asprintf("%d", player->getPass()));

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
    QLabel *accuracyLabel = new QLabel("Accuracy : " + QString::asprintf("%.1f", player->getAccuracy()) + "%");
    QLabel *noteLabel = new QLabel();
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
    QPushButton *restartButton = new QPushButton("Recommencer");
    buttonLayout->addStretch();
    buttonLayout->addWidget(menuButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(restartButton);
    buttonLayout->addStretch();

        //Right
    QPixmap pix(":/img/Background/Fever.png");

    QLabel *pixmap = new QLabel;
    pixmap->setPixmap(pix);

    mainLayout->addWidget(pixmap);
}
