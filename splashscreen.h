#pragma once

#include <QWidget>

class QPushButton;

class SplashScreen : public QWidget
{
public:
    SplashScreen(QWidget *parent = nullptr);

private:
    QPushButton *startButton;
};

