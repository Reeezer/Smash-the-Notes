#include "endscreen.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QString>

EndScreen::EndScreen(Game *game, Character *player, QWidget *parent)
    : QWidget(parent), game(game), player(player)
{
    //Black background
    setPalette(QPalette(QPalette::Background, Qt::black));
    setAutoFillBackground(true);

    //Main layout
    QHBoxLayout *mainLayout = new QHBoxLayout(this);

    //Left
    QVBoxLayout *leftLayout = new QVBoxLayout;
    mainLayout->addLayout(leftLayout);
    leftLayout->setAlignment(Qt::AlignCenter);

    //Up left
    QHBoxLayout *titleLayout = new QHBoxLayout;
    titleLayout->setAlignment(Qt::AlignCenter);
    leftLayout->addLayout(titleLayout);
    leftLayout->addStretch();

    QLabel *title = new QLabel("Victory");
    titleLayout->addWidget(title);

    //Middle left
    QGridLayout *labelLayout = new QGridLayout;
    leftLayout->addStretch();
    leftLayout->addLayout(labelLayout);

    QLabel *scoreLabel = new QLabel("Score : " + QString::asprintf("%d", player->getScore()));
    QLabel *highScoreLabel = new QLabel("High score : " + QString::asprintf("%d", 0));
    QLabel *perfectLabel = new QLabel("Perfect : " + QString::asprintf("%d", player->getPerfect()));
    QLabel *greatLabel = new QLabel("Great : " + QString::asprintf("%d", player->getGreat()));
    QLabel *missLabel = new QLabel("Miss : " + QString::asprintf("%d", player->getMiss()));
    QLabel *passLabel = new QLabel("Pass : " + QString::asprintf("%d", player->getPass()));
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

    labelLayout->addWidget(scoreLabel, 0 ,0);
    labelLayout->addWidget(highScoreLabel, 0, 2);
    labelLayout->addWidget(perfectLabel, 1, 0);
    labelLayout->addWidget(greatLabel, 1, 2);
    labelLayout->addWidget(missLabel, 2, 0);
    labelLayout->addWidget(passLabel, 2, 2);
    labelLayout->addWidget(accuracyLabel, 3, 1);
    labelLayout->addWidget(noteLabel, 4, 1);

    accuracyLabel->setAlignment(Qt::AlignCenter);
    noteLabel->setAlignment(Qt::AlignCenter);

    //Bottom left
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    leftLayout->addStretch();
    leftLayout->addLayout(buttonLayout);
    leftLayout->addStretch();

    QPushButton *menuButton = new QPushButton("Menu");
    QPushButton *settingsButton = new QPushButton("Paramètres");
    QPushButton *restartButton = new QPushButton("Recommencer");
    buttonLayout->addStretch();
    buttonLayout->addWidget(menuButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(settingsButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(restartButton);
    buttonLayout->addStretch();

    //Right
    QPixmap pix(":/img/Background/Fever.png");

    QLabel *pixmap = new QLabel;
    pixmap->setPixmap(pix);
    pixmap->setScaledContents(true);

    mainLayout->addWidget(pixmap);
}
