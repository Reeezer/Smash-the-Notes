#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent)
    : QWidget(parent)
{
    startButton = new QPushButton(tr("Click here or press Enter"), this);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(startButton, 1);
    layout->addStretch(0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addLayout(layout, 1);
    layout2->addStretch(0);

    setLayout(layout2);

    connect(startButton, &QPushButton::clicked, this, &SplashScreen::splashScreenPass);
}

void SplashScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
        emit mainMenuCall();
}

void SplashScreen::splashScreenPass()
{
    emit mainMenuCall();
}
