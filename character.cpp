#include "character.h"

#define MAXHEALTH 300
#define MAXFEVER 100
#define DAMAGE 30
#define REGENERATION 80
#define FEVERDECREASE 10

Character::Character()
{
    life = MAXHEALTH;
    fever = score = nbPerfect = nbGreat = 0;
    combo = 1;
    hasJumped = isFevered = false;
    alive = true;
}

void Character::damage()
{
    life -= DAMAGE;
    if(life <= 0){
        alive = false;
        life = 0;
    }
}

void Character::regenerate()
{
    life += REGENERATION;
    if(life >= MAXHEALTH)
        life = MAXHEALTH;
}

void Character::setJump(bool state)
{
    hasJumped = state;
}

void Character::increaseFever()
{
    fever++;
    if(fever >= MAXFEVER){
        fever = MAXFEVER;
        isFevered = true;
    }
}

void Character::feverModeDecrease()
{
    fever -= FEVERDECREASE;
    if(fever <= 0)
        fever = 0;
}

void Character::increaseCombo()
{
    combo++;
}

void Character::comboBreak()
{
    combo = 1;
}

void Character::increaseScorePerfect()
{
    score += 200 * combo;
    nbPerfect++;
}

void Character::increaseScoreGreat()
{
    score += 100 * combo;
    nbGreat++;
}

int Character::getCombo()
{
    return combo;
}

int Character::getFever()
{
    return fever;
}

int Character::getLife()
{
    return life;
}

int Character::getScore()
{
    return score;
}

bool Character::getJump()
{
    return hasJumped;
}

bool Character::getAlive()
{
    return alive;
}
