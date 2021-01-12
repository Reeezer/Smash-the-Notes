#ifndef CHARACTER_H
#define CHARACTER_H

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
    void damage();
    void regenerate();
    void increaseFever();
    void feverModeDecrease();
    void setJump(bool);
    void increaseCombo();
    void comboBreak();
    void increaseScore();
    void increaseScoreGreat();
    void increaseScorePerfect();
    void increaseMiss();
    void increasePass();
    void setState(CharacterAction);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

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
    bool getJump();
    bool getAlive();
    bool getFevered();

private:
    QElapsedTimer *timer;
    int _life, _combo, _score, _nbPerfect, _nbGreat, _nbMiss, _nbPass, _framesNb, _lastElapsed;
    float _fever;
    bool _hasJumped, _isFevered, _alive;
    CharacterAction _state;

    Animatable _frames[CHARACTERACTION_ESIZE];
};

#endif // CHARACTER_H
