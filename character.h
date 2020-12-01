#ifndef CHARACTER_H
#define CHARACTER_H


class Character
{
public:
    Character();
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

    int getFever();
    int getLife();
    int getScore();
    int getCombo();
    int getPerfect();
    int getGreat();
    int getMiss();
    int getPass();
    bool getJump();
    bool getAlive();
    bool getFevered();
private:
    int life, fever, combo, score, nbPerfect, nbGreat, nbMiss, nbPass;
    bool hasJumped, isFevered, alive;
};

#endif // CHARACTER_H
