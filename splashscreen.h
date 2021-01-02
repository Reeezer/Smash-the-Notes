#pragma once

#include <QWidget>
#include <QPushButton>

class SplashScreen : public QWidget
{
public:
    SplashScreen(QWidget *parent = nullptr);

private:
    QPushButton *startButton;
};

