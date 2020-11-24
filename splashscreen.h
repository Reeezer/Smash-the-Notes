#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QPushButton>

class SplashScreen : public QWidget
{
public:
    SplashScreen(QWidget *parent = nullptr);

private:
    QPushButton *startButton;
};

#endif // SPLASHSCREEN_H
