#include "endscreen.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>

EndScreen::EndScreen(Game *game, QWidget *parent)
    : QWidget(parent), game(game)
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

    QLabel *scoreLabel = new QLabel("Score : 0");
    QLabel *highScoreLabel = new QLabel("High score : 0");
    QLabel *perfectLabel = new QLabel("Perfect : 0");
    QLabel *greatLabel = new QLabel("Great : 0");
    QLabel *missLabel = new QLabel("Miss : 0");
    QLabel *passLabel = new QLabel("Pass : 0");
    QLabel *accuracyLabel = new QLabel("Accuracy : 0");
    labelLayout->addWidget(scoreLabel, 0 ,0);
    labelLayout->addWidget(highScoreLabel, 0, 2);
    labelLayout->addWidget(perfectLabel, 1, 0);
    labelLayout->addWidget(greatLabel, 1, 2);
    labelLayout->addWidget(missLabel, 2, 0);
    labelLayout->addWidget(passLabel, 2, 2);
    labelLayout->addWidget(accuracyLabel, 3, 1);

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
