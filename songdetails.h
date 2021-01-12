#pragma once

#include <QWidget>

class QLabel;
class QPixmap;
class QListWidget;

#include "game.h"

class SongDetails : public QWidget
{
public:
    SongDetails(Game *game, QWidget *parent = nullptr);

private:
    Game *game;

    QLabel *titleLabel;
    QLabel *highscoreLabel;
    QLabel *rankLabel;
    QPixmap *rankIcon;

    QListWidget *highscoreList;
};
