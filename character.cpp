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
    if(fever <= 0){
        fever = 0;
        isFevered = false;
    }
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

void Character::increaseScore() {score += 50 * combo;}
void Character::increaseCombo() {combo++;}
void Character::comboBreak() {combo = 1;}
void Character::setJump(bool state) {hasJumped = state;}
void Character::increaseMiss() {nbMiss++;}
void Character::increasePass() {nbPass++;}

int Character::getCombo() {return combo;}
int Character::getFever() {return fever;}
int Character::getLife() {return life;}
int Character::getScore() {return score;}
int Character::getPerfect() {return nbPerfect;}
int Character::getGreat() {return nbGreat;}
int Character::getMiss() {return nbMiss;}
int Character::getPass() {return nbPass;}
bool Character::getJump() {return hasJumped;}
bool Character::getAlive() {return alive;}
bool Character::getFevered() {return isFevered;}
