#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QList>
#include <QGraphicsItem>
#include <QTimerEvent>

const int PERFECT = 20;
const int GREAT = 20;
const int NOTPASSED = 300;
const int XLINE = 100;

class QGraphicsScene;
class QMediaPlayer;
class QGraphicsItem;
class QLabel;
class QTime;

#include "GameItems\character.h"
#include "game.h"
#include "GameItems\note.h"
//class Song; //TODO : change to include when Song is implemented

class GameView : public QGraphicsView
{
public:
    GameView(Game *game, QWidget *parent = nullptr);
    void update();
    void playerHit(QList<Note *> *);
    void checkPass(QList<Note *> *, bool);
    void hitSmash();
    void removeNote(QList<Note *> *);
    void changeNotePosition(QList<Note *> *);

private:
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
    Game *game;

    QGraphicsScene *scene;
    QMediaPlayer *music;
    Character *player;
    QTime *timer;

    QGraphicsSimpleTextItem *timeLabel, *feverLabel, *scoreLabel, *comboLabel, *lifeLabel;
    QList<Note *> *upNotes, *downNotes;
};

#endif // GAMEVIEW_H
