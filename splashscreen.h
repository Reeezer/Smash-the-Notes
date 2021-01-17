#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QKeyEvent>

class SplashScreen : public QWidget
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);

private:
    void keyPressEvent(QKeyEvent *);

    QPushButton *startButton;

signals:
    void mainMenuCall();

public slots:
    void splashScreenPass();
};

