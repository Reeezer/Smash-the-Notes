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
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::black));
    setStyleSheet("QPushButton { color: white; background-color: gray } QLabel {color : white}");

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
    title->setFont(game->fonts[FontType::NORMAL_50]);

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

    highScoreLabel->setAlignment(Qt::AlignRight);
    greatLabel->setAlignment(Qt::AlignRight);
    passLabel->setAlignment(Qt::AlignRight);

    labelLayout->addWidget(scoreLabel, 0 , 0);
    labelLayout->addWidget(highScoreLabel, 0, 1);
    labelLayout->addWidget(perfectLabel, 1, 0);
    labelLayout->addWidget(greatLabel, 1, 1);
    labelLayout->addWidget(missLabel, 2, 0);
    labelLayout->addWidget(passLabel, 2, 1);

    scoreLabel->setFont(game->fonts[FontType::NORMAL_18]);
    highScoreLabel->setFont(game->fonts[FontType::NORMAL_18]);
    perfectLabel->setFont(game->fonts[FontType::NORMAL_18]);
    greatLabel->setFont(game->fonts[FontType::NORMAL_18]);
    missLabel->setFont(game->fonts[FontType::NORMAL_18]);
    passLabel->setFont(game->fonts[FontType::NORMAL_18]);

            //Accuracy Left
    QVBoxLayout *accuracyLayout = new QVBoxLayout;
    leftLayout->addLayout(accuracyLayout);
    accuracyLabel = new QLabel();
    noteLabel = new QLabel();

    accuracyLabel->setFont(game->fonts[FontType::NORMAL_18]);
    noteLabel->setFont(game->fonts[FontType::NORMAL_40]);
    accuracyLabel->setAlignment(Qt::AlignCenter);
    noteLabel->setAlignment(Qt::AlignCenter);

    accuracyLayout->addWidget(accuracyLabel);
    accuracyLayout->addWidget(noteLabel);

            //Button left
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    leftLayout->addStretch();
    leftLayout->addLayout(buttonLayout);
    leftLayout->addStretch();

    QPushButton *menuButton = new QPushButton(QIcon(":/img/Icons/PNG/Black/1x/home.png"), "Menu");
    QPushButton *restartButton = new QPushButton(QIcon(":/img/Icons/PNG/Black/1x/return.png"), "Restart");
    buttonLayout->addStretch();
    buttonLayout->addWidget(menuButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(restartButton);
    buttonLayout->addStretch();

        //Right
    QPixmap pix(":/img/Background/EndScreen.png");

    QLabel *pixmap = new QLabel;
    pixmap->setPixmap(pix.scaled(450, 600));

    mainLayout->addWidget(pixmap);

    //Connect
    QObject::connect(restartButton, &QPushButton::clicked, this, &EndScreen::restartGame);
    QObject::connect(menuButton, &QPushButton::clicked, this, &EndScreen::returnToMenu);
}

EndScreen::~EndScreen()
{
}


void EndScreen::initialize()
{
    scoreLabel->setText("Score : " + QString::asprintf("%d", player->getScore()));
    highScoreLabel->setText(QString::asprintf("%d", 0) + " : High score");
    perfectLabel->setText("Perfect : " + QString::asprintf("%d", player->getPerfect()));
    greatLabel->setText(QString::asprintf("%d", player->getGreat()) + " : Great");
    missLabel->setText("Miss : " + QString::asprintf("%d", player->getMiss()));
    passLabel->setText(QString::asprintf("%d", player->getPass()) + " : Pass");
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
