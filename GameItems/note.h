#ifndef NOTE_H
#define NOTE_H

#include <QGraphicsPixmapItem>
class QPixmap;
class QPainter;
class QWidget;
class QElapsedTimer;

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

    int getTimestamp();
    NoteType getNoteType();
    int getMaxHits();
    int getPoints();
    int getTimeout();
    int getHit();
    void hit();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QElapsedTimer *timer;
    NoteType _noteType;
    int _timestamp, _maxHits, _points, _timeout, _hits, _frameHeight, _maxFrame, _framesNb, _frameWidth, _lastElapsed;
    QPixmap *sprite;
};

#endif // NOTE_H
