#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QPushButton>

class SplashScreen : public QPushButton
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);

signals:
    void displayMainMenu();

protected:
    void keyPressEvent(QKeyEvent *);
};

#endif // SPLASHSCREEN_H
