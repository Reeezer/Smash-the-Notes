#include "endscreen.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QString>
#include <QKeyEvent>
#include <QSizePolicy>
#include <QDebug>

EndScreen::EndScreen(GameData *game, Character *player, QWidget *parent)
    : QWidget(parent), _game(game), _player(player)
{
    setAttribute(Qt::WA_StyledBackground, true);
    setStyleSheet("EndScreen { background-color: black; } QLabel { background-color: black; color: white; }");

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
    title->setFont(game->_fonts[FontType::NORMAL_50]);

            //Results left
    QGridLayout *labelLayout = new QGridLayout;
    leftLayout->addStretch();
    leftLayout->addLayout(labelLayout);

    _scoreLabel = new QLabel();
    _highScoreLabel = new QLabel();
    _perfectLabel = new QLabel();
    _greatLabel = new QLabel();
    _missLabel = new QLabel();
    _passLabel = new QLabel();

    _highScoreLabel->setAlignment(Qt::AlignRight);
    _greatLabel->setAlignment(Qt::AlignRight);
    _passLabel->setAlignment(Qt::AlignRight);

    labelLayout->addWidget(_scoreLabel, 0 , 0);
    labelLayout->addWidget(_highScoreLabel, 0, 1);
    labelLayout->addWidget(_perfectLabel, 1, 0);
    labelLayout->addWidget(_greatLabel, 1, 1);
    labelLayout->addWidget(_missLabel, 2, 0);
    labelLayout->addWidget(_passLabel, 2, 1);

    _scoreLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _highScoreLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _perfectLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _greatLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _missLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _passLabel->setFont(game->_fonts[FontType::NORMAL_18]);

            //Accuracy Left
    QVBoxLayout *accuracyLayout = new QVBoxLayout;
    leftLayout->addLayout(accuracyLayout);
    _accuracyLabel = new QLabel();
    _noteLabel = new QLabel();

    _accuracyLabel->setFont(game->_fonts[FontType::NORMAL_18]);
    _noteLabel->setFont(game->_fonts[FontType::NORMAL_40]);
    _accuracyLabel->setAlignment(Qt::AlignCenter);
    _noteLabel->setAlignment(Qt::AlignCenter);

    accuracyLayout->addWidget(_accuracyLabel);
    accuracyLayout->addWidget(_noteLabel);

            //Button left
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    leftLayout->addStretch();
    leftLayout->addLayout(buttonLayout);
    leftLayout->addStretch();

    QPushButton *menuButton = new QPushButton(QIcon(":/img/Icons/home.png"), "Menu");
    menuButton->setIconSize(QSize(40, 40));
    menuButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    _restartButton = new QPushButton(QIcon(":/img/Icons/return.png"), "Restart");
    _restartButton->setIconSize(QSize(40, 40));
    _restartButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    buttonLayout->addWidget(menuButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(_restartButton);

        //Right
    QPixmap pix(":/img/Background/EndScreen.png");

    QLabel *pixmap = new QLabel;
    pixmap->setPixmap(pix.scaled(450, 450));

    mainLayout->addWidget(pixmap);

    //Connect
    QObject::connect(_restartButton, &QPushButton::clicked, this, &EndScreen::restartGame);
    QObject::connect(menuButton, &QPushButton::clicked, this, &EndScreen::displayMainMenu);
}

EndScreen::~EndScreen()
{
}

void EndScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == _game->_resetButtonKey)
        emit _restartButton->clicked();
}

void EndScreen::initialize()
{
    _scoreLabel->setText("Score : " + QString::asprintf("%d", _player->getScore()));
    _highScoreLabel->setText(QString::asprintf("%d", 0) + " : High score");
    _perfectLabel->setText("Perfect : " + QString::asprintf("%d", _player->getPerfect()));
    _greatLabel->setText(QString::asprintf("%d", _player->getGreat()) + " : Great");
    _missLabel->setText("Miss : " + QString::asprintf("%d", _player->getMiss()));
    _passLabel->setText(QString::asprintf("%d", _player->getPass()) + " : Pass");
    _accuracyLabel->setText("Accuracy : " + QString::asprintf("%.1f", _player->getAccuracy()) + "%");

    if(_player->getAccuracy() > 99)
        _noteLabel->setText("S++");
    else if(_player->getAccuracy() > 95)
        _noteLabel->setText("S+");
    else if(_player->getAccuracy() > 90)
        _noteLabel->setText("S");
    else if(_player->getAccuracy() > 80)
        _noteLabel->setText("A");
    else if(_player->getAccuracy() > 70)
        _noteLabel->setText("B");
    else if(_player->getAccuracy() > 50)
        _noteLabel->setText("C");
    else
        _noteLabel->setText("D");
}
