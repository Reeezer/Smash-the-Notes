#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QList>
#include <QGraphicsItem>
#include <QLabel>

#include "character.h"
#include "game.h"

class GameView : public QGraphicsView
{
public:
    GameView(Game *game, QWidget *parent = nullptr);
    void _update();
    void playerHit(QList<Note *>);
    void checkPass(QList<Note *>);
protected:
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
private:
    Game *game;

    QGraphicsScene *scene;
    QMediaPlayer *music;
    Character *player;
    QTime *timer;
    qint64 musicPosition;

    QLabel *timeLabel, *feverLabel, *scoreLabel, *comboLabel, *lifeLabel;
    QList<Note *> upNotes, downNotes;
};

#endif // GAMEVIEW_H
