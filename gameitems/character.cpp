#include "character.h"

#include <QDebug>
#include <QElapsedTimer>
#include <QPainter>
#include <QPixmap>
#include <QStyleOptionGraphicsItem>

Character::Character(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    _frames[RUN] = Animatable(":/img/Character/Run/run%d.png", 15, 30);
    _frames[DOWN] = Animatable(":/img/Character/Down/down%d.png", 1, 30);
    _frames[REGENERATE] = Animatable(":/img/Character/Regenerate/regenerate%d.png", 16, 30);
    _frames[FEVER] = Animatable(":/img/Character/Fever/fever%d.png", 13, 30);
    _frames[DAMAGED] = Animatable(":/img/Character/Damage/damage%d.png", 11, 30);
    _frames[HIT] = Animatable(":/img/Character/Hit/hit%d.png", 15, 30);
    _frames[JUMP] = Animatable(":/img/Character/Jump/jump%d.png", 24, 30);

    _timer = new QElapsedTimer();
    _timer->start();
    resetCharacter();
}

void Character::resetCharacter()
{
    _state = CharacterAction::RUN;
    _life = MAXLIFE;
    _fever = _score = _combo = _nbPerfect = _nbGreat = _framesNb = _lastElapsed = _accuracy = _nbPass = _nbMiss = 0;
    _hasJumped = _isFevered = false;
    _alive = true;

    for (int i = 0; i < CHARACTERACTION_ESIZE; i++)
        _frames->reset();

    _timer = new QElapsedTimer();
    _timer->restart();
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(-125, -140, 300, 300, _frames[_state].getCurrentPixmap());
    if (_frames[_state].update(_timer->elapsed()))
    {
        if (_state != CharacterAction::DOWN)
            _state = CharacterAction::RUN;
    }
}

void Character::damage()
{
    _life -= DAMAGE;
    if (_life <= 0)
    {
        _alive = false;
        _life = 0;
    }
}

void Character::regenerate()
{
    _life += REGENERATION;
    if (_life >= MAXLIFE)
        _life = MAXLIFE;
}

void Character::increaseFever()
{
    _fever += 5;
    if (_fever >= MAXFEVER)
    {
        _fever = MAXFEVER;
        _isFevered = true;
    }
}

void Character::feverModeDecrease()
{
    _fever -= 0.06;
    if (_fever <= 0)
    {
        _fever = 0;
        _isFevered = false;
    }
}

void Character::increaseScorePerfect()
{
    if (_isFevered)
        _score += 500;
    else
        _score += 200;
    _nbPerfect++;
}

void Character::increaseScoreGreat()
{
    if (_isFevered)
        _score += 300;
    else
        _score += 100;
    _nbGreat++;
}

void Character::increaseScore()
{
    if (_isFevered)
        _score += 150;
    else
        _score += 50;
}

void Character::setState(CharacterAction stateSource)
{
    _frames[_state].reset();
    _state = stateSource;
    if (stateSource == CharacterAction::HIT)
        _frames[_state].reset(9);
    else
        _frames[_state].reset();
}

void Character::increaseCombo() { _combo++; }
void Character::comboBreak() { _combo = 0; }
void Character::setJump(bool _state) { _hasJumped = _state; }
void Character::increaseMiss() { _nbMiss++; }
void Character::increasePass() { _nbPass++; }

int Character::getCombo() { return _combo; }
int Character::getFever() { return _fever; }
int Character::getLife() { return _life; }
int Character::getScore() { return _score; }
int Character::getPerfect() { return _nbPerfect; }
int Character::getGreat() { return _nbGreat; }
int Character::getMiss() { return _nbMiss; }
int Character::getPass() { return _nbPass; }
int Character::getMaxLife() { return MAXLIFE; }
int Character::getMaxFever() { return MAXFEVER; }
float Character::getAccuracy() { return 100 * (_nbPerfect + (0.75 * _nbGreat)) / (_nbGreat + _nbPerfect + _nbMiss + _nbPass); }
bool Character::getJump() { return _hasJumped; }
bool Character::getAlive() { return _alive; }
bool Character::getFevered() { return _isFevered; }
