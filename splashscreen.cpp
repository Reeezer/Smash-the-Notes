#include "splashscreen.h"

#include <QKeyEvent>

SplashScreen::SplashScreen(QWidget *parent)
    : QPushButton(parent)
{
    setStyleSheet("SplashScreen {background-image: url(\":/img/smashthenotes.png\"); border: 0px;} SplashScreen:hover {border: 0px; }");
    setText("");
    connect(this, &QPushButton::clicked, this, &SplashScreen::displayMainMenu);
}

void SplashScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
        emit displayMainMenu();
}
