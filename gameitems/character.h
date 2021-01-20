#pragma once

const int MAXLIFE = 300;
const int MAXFEVER = 100;
const int DAMAGE = 30;
const int REGENERATION = 80;

#include <QGraphicsPixmapItem>

#include "animatable.h"

class QPixmap;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;
class QElapsedTimer;

enum CharacterAction
{
    RUN,
    DOWN,
    REGENERATE,
    FEVER,
    DAMAGED,
    HIT,
    JUMP,
    CHARACTERACTION_ESIZE
};

class Character : public QGraphicsPixmapItem
{
public:
    Character(QGraphicsItem *parent = nullptr);

    void initialize();
    void damage();
    void regenerate();
    void increaseFever();
    void feverModeDecrease();
    void increaseCombo();
    void comboBreak();
    void increaseScore();
    void increaseScoreGreat();
    void increaseScorePerfect();
    void increaseMiss();
    void increasePass();

    /* getters */
    int getFever();
    int getLife();
    int getScore();
    int getCombo();
    int getPerfect();
    int getGreat();
    int getMiss();
    int getPass();
    int getMaxFever();
    int getMaxLife();
    float getAccuracy();
    bool getJump();
    bool getAlive();
    bool getFevered();

    /* setters */
    void setJump(bool);
    void setState(CharacterAction);

protected:
    /* méthodes Qt */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QElapsedTimer *_timer;
    int _life;
    int _combo;
    int _score;
    int _nbPerfect, _nbGreat, _nbMiss, _nbPass;
    int _framesNb, _lastElapsed;
    float _fever, _accuracy;
    bool _hasJumped, _isFevered, _alive;
    CharacterAction _state;

    Animatable _frames[CHARACTERACTION_ESIZE];
};

