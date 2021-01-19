#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent)
    : QPushButton(parent)
{
    setText(tr("Click here or press Enter"));
    connect(this, &QPushButton::clicked, this, &SplashScreen::displayMainMenu);
}

void SplashScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
        emit displayMainMenu();
}

