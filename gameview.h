#pragma once

#include <QGraphicsView>
#include <QList>
#include <QObject>

const int PERFECT = 10;
const int GREAT = 20;
const int NOTPASSED = 140;
const int PIXMAPHALF = 40;
const int NBSMASHHIT = 20;

class QGraphicsScene;
class QMediaPlayer;
class QGraphicsItem;
class QLabel;
class QTime;
class QElapsedTimer;
class QGraphicsItem;
class QPushButton;
class QSoundEffect;

#include "gameitems/character.h"
#include "game.h"
#include "fileutils.h"
#include "gameitems/note.h"
#include "song.h"

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(Game *game, Character *player, QWidget *parent = nullptr);
    void update();
    void hitNormal(QList<Note *> *);
    void checkPass(QList<Note *> *, bool);
    void hitSmash(QList<Note *> *);
    void removeFirstNote(QList<Note *> *);
    void removeNoteHitten(QList<Note *> *);
    void changeNotePosition(QList<Note *> *);
    void changeLabel(QString, bool);
    void applyParallax(float, QList<QGraphicsPixmapItem *> *);
    void backgroundDisplay();
    void rotateCrossHair();
    void gamePause();
    void hit();
    Note *getNextNote(QList<Note *> *);
    Song *getCurrentSong();

public slots:
    void newGame(Song *);
    void restartGame();
    void musicEnd();

signals:
    void displayEndScreen();
    void displayMainMenu();

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

    QGraphicsPixmapItem *pixUpCross, *pixDownCross, *backgroundFever, *backLayer;

    QGraphicsSimpleTextItem *score, *combo, *highScore, *upLabel, *downLabel, *gameOverLabel, *pauseLabel;
    QGraphicsRectItem *lifeRect, *feverRect, *durationRect;

    QList<Note *> *upNotes, *downNotes;
    QList<QGraphicsPixmapItem *> *backgroundList;
    QList<QPixmap> *crosshairList;
    int XLINE, UPLINE, DOWNLINE, _highScore, _lastBackgroundElapsed, _rotationCrossHair, _countCross, _lastJumpElapsed, _lastSmashElapsed;
    float _ratio;
    bool _pause;

    Song *_currentSong;
};

