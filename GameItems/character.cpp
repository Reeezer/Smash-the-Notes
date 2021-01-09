#include "character.h"
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QDebug>
#include <QElapsedTimer>

Character::Character(Animatable (*frames)[CHARACTERACTION_ESIZE], QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), _frames(frames)
{
    _state = CharacterAction::RUN;
    _life = MAXLIFE;
    _fever = _score = _nbPerfect = _nbGreat = _framesNb = _lastElapsed = 0;
    _combo = 1;
    _hasJumped = _isFevered = false;
    _alive = true;

    timer = new QElapsedTimer();
    timer->start();
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-125, -140, 300, 300, (*_frames)[_state].currentPixmap());

    if((*_frames)[_state].update(timer->elapsed()))
    {
        if(_state != CharacterAction::DOWN)
            _state = CharacterAction::RUN;
    }
}

void Character::damage()
{
    _life -= DAMAGE;
    if(_life <= 0)
    {
        _alive = false;
        _life = 0;
    }
}

void Character::regenerate()
{
    _life += REGENERATION;
    if(_life >= MAXLIFE)
        _life = MAXLIFE;
}

void Character::increaseFever()
{
    _fever += 5;
    if(_fever >= MAXFEVER)
    {
        _fever = MAXFEVER;
        _isFevered = true;
    }
}

void Character::feverModeDecrease()
{
    _fever -= 0.06;
    if(_fever <= 0)
    {
        _fever = 0;
        _isFevered = false;
    }
}

void Character::increaseScorePerfect()
{
    if(_isFevered)
        _score += 500 * _combo;
    else
        _score += 200 * _combo;
    _nbPerfect++;
}

void Character::increaseScoreGreat()
{
    if(_isFevered)
        _score += 300 * _combo;
    else
        _score += 100 * _combo;
    _nbGreat++;
}

void Character::increaseScore()
{
    if(_isFevered)
        _score += 150 * _combo;
    else
    _score += 50 * _combo;
}

void Character::setState(CharacterAction stateSource)
{
    (*_frames)[_state].reset();
    _state = stateSource;
    if(stateSource == CharacterAction::HIT)
        (*_frames)[_state].reset(9);
    else
        (*_frames)[_state].reset();
}

void Character::increaseCombo() {_combo++;}
void Character::comboBreak() {_combo = 1;}
void Character::setJump(bool _state) {_hasJumped = _state;}
void Character::increaseMiss() {_nbMiss++;}
void Character::increasePass() {_nbPass++;}

int Character::getCombo() {return _combo;}
int Character::getFever() {return _fever;}
int Character::getLife() {return _life;}
int Character::getScore() {return _score;}
int Character::getPerfect() {return _nbPerfect;}
int Character::getGreat() {return _nbGreat;}
int Character::getMiss() {return _nbMiss;}
int Character::getPass() {return _nbPass;}
int Character::getMaxLife() {return MAXLIFE;}
int Character::getMaxFever() {return MAXFEVER;}
bool Character::getJump() {return _hasJumped;}
bool Character::getAlive() {return _alive;}
bool Character::getFevered() {return _isFevered;}
