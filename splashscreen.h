#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QPushButton>

class SplashScreen : public QPushButton
{
    Q_OBJECT

public:
    SplashScreen(QWidget *parent = nullptr);

public slots:
    void flash();

signals:
    void displayMainMenu();

protected:
    void keyPressEvent(QKeyEvent *);

private:
    bool _textIsVisible;
};

#endif // SPLASHSCREEN_H
