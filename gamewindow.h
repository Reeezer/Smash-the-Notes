#ifndef DISPLAY_H
#define DISPLAY_H

#include <QStackedWidget>

#include "gameview.h"
#include "mainsettings.h"
#include "controlsettings.h"

class GameWindow : public QStackedWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
};
#endif // DISPLAY_H
