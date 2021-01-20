#pragma once

#include <QGraphicsPixmapItem>

class QPixmap;
class QPainter;
class QWidget;
class QElapsedTimer;
class QStyleOptionGraphicsItem;

const int TIMEOUT = 80;

enum NoteType
{
    NORMALUP,
    NORMALDOWN,
    BONUS,
    TRAP,
    SMASH
};

class Note : public QGraphicsPixmapItem
{
public:
    Note(NoteType , int,QGraphicsItem *parent = nullptr);

    void hit();

    /* getters */

    int getTimeStamp();
    NoteType getNoteType();
    int getTimeOut();
    int getHit();

protected:
    /* méthodes Qt */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QElapsedTimer *_timer;
    NoteType _noteType;
    int _timeStamp, _timeOut, _hits, _frameHeight, _maxFrame, _framesNb, _frameWidth, _lastElapsed;
    QPixmap *_sprite;
};

