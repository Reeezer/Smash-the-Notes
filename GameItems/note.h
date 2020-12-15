#ifndef NOTE_H
#define NOTE_H

#include <QGraphicsPixmapItem>
class QPixmap;
class QPainter;
class QWidget;

enum NoteType
{
    NORMAL,
    BONUS,
    TRAP,
    SMASH
};

class Note : public QGraphicsPixmapItem
{
public:
    Note(NoteType , int, QGraphicsItem *parent = nullptr);

    int getTimestamp();
    NoteType getNoteType();
    int getMaxHits();
    int getPoints();
    int getTimeout();
    int getHit();
    void hit();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    //Pour les tests manuels
    int _timestamp;
    NoteType _noteType;

private:
    int _maxHits;
    int _points;
    int _timeout;
    QPixmap _frames;//At this time we work with a frame, note a table of frames
    int _hits;
};

#endif // NOTE_H
