#pragma once

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>

class SplashScreen : public QPushButton
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent *);

signals:
    void mainMenuCall();

public slots:
    void splashScreenPass();
};

