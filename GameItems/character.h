#ifndef CHARACTER_H
#define CHARACTER_H

const int MAXHEALTH = 300;
const int MAXFEVER = 100;
const int DAMAGE = 30;
const int REGENERATION = 80;
const int FEVERDECREASE = 10;

#include <QGraphicsPixmapItem>

class QPixmap;
class QPainter;
class QStyleOptionGraphicsItem;
class QWidget;

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
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

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
    int _life, _fever, _combo, _score, _nbPerfect, _nbGreat, _nbMiss, _nbPass;
    bool _hasJumped, _isFevered, _alive;
};

#endif // CHARACTER_H
