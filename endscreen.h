#pragma once

#include <QWidget>

#include "game.h"

class EndScreen : public QWidget
{
public:
    EndScreen(Game *game, QWidget *parent = nullptr);

private:
    Game *game;
};

