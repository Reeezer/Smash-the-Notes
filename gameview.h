#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QList>

const int PERFECT = 10;
const int GREAT = 20;
const int NOTPASSED = 140;
const int PIXMAPHALF = 40;

class QGraphicsScene;
class QMediaPlayer;
class QGraphicsItem;
class QLabel;
class QTime;
class QElapsedTimer;
class QGraphicsItem;
class QPushButton;

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
    void hitSmash(QList<Note *> *);
    void removeNotePassed(QList<Note *> *);
    void removeNoteHitten(QList<Note *> *);
    void changeNotePosition(QList<Note *> *);
    void changeLabel(QString, bool);
    void applyParallax(float, QList<QGraphicsPixmapItem *> *);
    void backgroundDisplay();
    void rotateCrossHair();
    void gamePause();
    Note* getNextNote(QList<Note *> *);

public slots:
    void initialize();

private:
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);
    Game *game;

    QGraphicsScene *scene;
    QMediaPlayer *music;
    QSoundEffect *hitEffect;
    Character *player;
    QElapsedTimer *timer;

    QPushButton *restartButton, *quitButton;

    QGraphicsPixmapItem *pixUpCross, *pixDownCross, *backgroundFever;

    QGraphicsSimpleTextItem *score, *combo, *highScore, *upLabel, *downLabel, *gameOverLabel, *pauseLabel;
    QGraphicsRectItem *lifeRect, *feverRect, *durationRect;

    QList<Note *> *upNotes, *downNotes;
    QList<QGraphicsPixmapItem *> *backgroundList;
    int XLINE, UPLINE, DOWNLINE, _highScore, _lastElapsed, _rotationCrossHair, _countCross, _lastJumpElapsed;
    float _ratio;
    bool _pause;
};

#endif // GAMEVIEW_H
