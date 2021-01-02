#pragma once

#include <QStackedWidget>

#include "GameItems/character.h"
#include "gameview.h"
#include "endscreen.h"

class GameWindow : public QStackedWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
};

