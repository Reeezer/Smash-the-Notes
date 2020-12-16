#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QList>
#include <QGraphicsItem>
#include <QTimerEvent>

const int PERFECT = 10;
const int GREAT = 20;
const int NOTPASSED = 80;
const int PIXMAPHALF = 25;

class QGraphicsScene;
class QMediaPlayer;
class QGraphicsItem;
class QLabel;
class QTime;

#include "GameItems/character.h"
#include "game.h"
#include "songfile.h"
#include "GameItems/note.h"
//class Song; //TODO : change to include when Song is implemented

class GameView : public QGraphicsView
{
public:
    GameView(Game *game, QWidget *parent = nullptr);
    void update();
    void hitNormal(QList<Note *> *);
    void checkPass(QList<Note *> *, bool);
    void hitSmash();
    void removeNotePassed(QList<Note *> *);
    void removeNoteHitten(QList<Note *> *);
    void changeNotePosition(QList<Note *> *);
    Note* getNextNote(QList<Note *> *);

private:
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
    Game *game;

    QGraphicsScene *scene;
    QMediaPlayer *music;
    QSoundEffect *hitEffect;
    Character *player;
    QTime *timer;

    QGraphicsSimpleTextItem *score, *combo, *highScore;
    QGraphicsRectItem *lifeRect, *feverRect, *durationRect;

    QList<Note *> *upNotes, *downNotes;
    int XLINE, UPLINE, DOWNLINE, _highScore;
};

#endif // GAMEVIEW_H
