#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QList>

const int PERFECT = 20;
const int GREAT = 20;
const int NOTPASSED = 300;

class QGraphicsScene;
class QMediaPlayer;
class QGraphicsItem;
class QLabel;
class QTime;

#include "character.h"
#include "game.h"

class GameView : public QGraphicsView
{
public:
    GameView(Game *game, QWidget *parent = nullptr);
    void update();
    void playerHit(QList<Note *>);
    void checkPass(QList<Note *>, bool);
    void hitSmash();

private:
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
    Game *game;

    QGraphicsScene *scene;
    QMediaPlayer *music;
    Character *player;
    QTime *timer;

    QLabel *timeLabel, *feverLabel, *scoreLabel, *comboLabel, *lifeLabel;
    QList<Note *> upNotes, downNotes;
};

#endif // GAMEVIEW_H
