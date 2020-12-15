#include "character.h"
#include <QPixmap>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QDebug>

Character::Character(QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent)
{
    _life = MAXHEALTH;
    _fever = _score = _nbPerfect = _nbGreat = 0;
    _combo = 1;
    _hasJumped = _isFevered = false;
    _alive = true;
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(30,0,70,80,QPixmap(":/img/Character.png"));
}

void Character::damage()
{
    _life -= DAMAGE;
    if(_life <= 0){
        _alive = false;
        _life = 0;
    }
}

void Character::regenerate()
{
    _life += REGENERATION;
    if(_life >= MAXHEALTH)
        _life = MAXHEALTH;
}

void Character::increaseFever()
{
    _fever++;
    if(_fever >= MAXFEVER){
        _fever = MAXFEVER;
        _isFevered = true;
    }
}

void Character::feverModeDecrease()
{
    _fever -= FEVERDECREASE;
    if(_fever <= 0){
        _fever = 0;
        _isFevered = false;
    }
}

void Character::increaseScorePerfect()
{
    _score += 200 * _combo;
    _nbPerfect++;
}

void Character::increaseScoreGreat()
{
    _score += 100 * _combo;
    _nbGreat++;
}

void Character::increaseScore() {_score += 50 * _combo;}
void Character::increaseCombo() {_combo++;}
void Character::comboBreak() {_combo = 1;}
void Character::setJump(bool state) {_hasJumped = state;}
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
bool Character::getJump() {return _hasJumped;}
bool Character::getAlive() {return _alive;}
bool Character::getFevered() {return _isFevered;}
