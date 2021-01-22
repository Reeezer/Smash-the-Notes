#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QList>

class QGraphicsScene;
class QGraphicsItem;
class QLabel;
class QTime;
class QElapsedTimer;
class QGraphicsItem;
class QPushButton;
class QSoundEffect;
class QMediaPlayer;

#include "gameitems/character.h"
#include "gamedata.h"
#include "fileutils.h"
#include "gameitems/note.h"
#include "song.h"

class GameView : public QGraphicsView
{
    Q_OBJECT

public:
    GameView(GameData *game, Character *player, QMediaPlayer *, QWidget *parent = nullptr);

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

    /* getters */
    Note *getNextNote(QList<Note *> *);
    Song *getCurrentSong();

public slots:
    void newGame(Song *);
    void restartGame();
    void musicEnd();

signals:
    void displayEndScreen();
    void displayMainMenu();

protected:
    /* methodes Qt */
    void keyPressEvent(QKeyEvent *);
    void timerEvent(QTimerEvent *);

private:
    GameData *_game;

    QGraphicsScene *_scene;
    QSoundEffect *_hitEffect;
    Character *_player;
    QElapsedTimer *_timer;
    QMediaPlayer *_music;

    QPushButton *_restartButton;
    QPushButton *_quitButton;

    QGraphicsPixmapItem *_pixUpCross;
    QGraphicsPixmapItem *_pixDownCross;
    QGraphicsPixmapItem *_backgroundFever;
    QGraphicsPixmapItem *_backLayer;

    QGraphicsSimpleTextItem *_score;
    QGraphicsSimpleTextItem *_combo;
    QGraphicsSimpleTextItem *_highScoreTextItem; // FIXME meilleurs nom
    QGraphicsSimpleTextItem *_upLabel;
    QGraphicsSimpleTextItem *_downLabel;
    QGraphicsSimpleTextItem *_gameOverLabel;
    QGraphicsSimpleTextItem *_pauseLabel;

    QGraphicsRectItem *_lifeRect;
    QGraphicsRectItem *_feverRect;
    QGraphicsRectItem *_durationRect;

    QList<Note *> *_upNotes, *_downNotes;
    QList<QGraphicsPixmapItem *> *_backgroundList;
    QList<QPixmap> *_crosshairList;
    // FIXME noms de variables en majuscule sans être constants
    int XLINE, UPLINE, DOWNLINE, _highScore, _lastBackgroundElapsed, _rotationCrossHair, _countCross, _lastJumpElapsed, _lastSmashElapsed;
    float _ratio;
    bool _pause;

    Song *_currentSong;
    bool _gameRunning; /* pour éviter que le signal du media player ne trigger un ajout aux highscores il faut qu'on sachge si on était en train de jouer*/

    /* constantes */
    const int PERFECT = 10;
    const int GREAT = 20;
    const int NOTPASSED = 140;
    const int PIXMAPHALF = 40;
    const int NBSMASHHIT = 20;
};

#endif // GAMEVIEW_H
