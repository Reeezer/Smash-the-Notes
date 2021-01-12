#include "splashscreen.h"

SplashScreen::SplashScreen(QWidget *parent)
    : QWidget(parent)
{
    startButton = new QPushButton(tr("Click here or press Enter"), this);
}
