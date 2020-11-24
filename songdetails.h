#ifndef SONGDETAILS_H
#define SONGDETAILS_H

#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QListWidget>

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

#endif // SONGDETAILS_H
