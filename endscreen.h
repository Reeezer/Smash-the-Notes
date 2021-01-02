#pragma once

#include <QWidget>

#include "game.h"
#include "GameItems/character.h"

class EndScreen : public QWidget
{
public:
    EndScreen(Game *game, Character *player, QWidget *parent = nullptr);

private:
    Game *game;
    Character *player;
};

