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
    void increaseScoreGreat();
    void increaseScorePerfect();

    int getFever();
    int getLife();
    int getScore();
    int getCombo();
    bool getJump();
    bool getAlive();
private:
    int life, fever, combo, score, nbPerfect, nbGreat;
    bool hasJumped, isFevered, alive;
};

#endif // CHARACTER_H
