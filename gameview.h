#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QList>
#include <QGraphicsItem>

#include "game.h"

class GameView : public QGraphicsView
{
public:
    GameView(Game *game, QWidget *parent = nullptr);

private:
    Game *game;

    QGraphicsScene *scene;
    QMediaPlayer *music;
    QList<QGraphicsItem *> notes;
};

#endif // GAMEVIEW_H
