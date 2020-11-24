#ifndef DISPLAY_H
#define DISPLAY_H

#include <QStackedWidget>

class GameWindow : public QStackedWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
};
#endif // DISPLAY_H
