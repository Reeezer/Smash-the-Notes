#include "splashscreen.h"

#include <QKeyEvent>
#include <QTimer>

SplashScreen::SplashScreen(QWidget *parent)
    : QPushButton(parent)
{
    setStyleSheet("SplashScreen {background-image: url(\":/img/smashthenotes.png\"); border: 0px; color: black;} SplashScreen:hover {border: 0px; }");
    setText("Click here or press return to start");
    _textIsVisible = false;

    connect(this, &QPushButton::clicked, this, &SplashScreen::displayMainMenu);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SplashScreen::flash);
    timer->setInterval(600);
    timer->start();
}

void SplashScreen::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return || event->key() == Qt::Key_Space)
        emit displayMainMenu();
}

void SplashScreen::flash()
{
    _textIsVisible = !_textIsVisible;
    if(_textIsVisible)
        setText("Click here or press return to start");
    else
        setText("");
}
