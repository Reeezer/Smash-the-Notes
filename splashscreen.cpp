#include "splashscreen.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>

SplashScreen::SplashScreen(QWidget *parent)
    : QPushButton(parent)
{
    setText(tr("Click here or press Enter"));
    connect(this, &QPushButton::clicked, this, &SplashScreen::displayMainMenu);
    setStyleSheet("SplashScreen {background-image: url(\":/img/smashthenotes.png\"); border: 0px;} SplashScreen:hover {border: 0px; }");
}

void SplashScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
        emit displayMainMenu();
}
