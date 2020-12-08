#ifndef NOTE_H
#define NOTE_H

#include <QGraphicsPixmapItem>
#include <QWidget>

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
    Note(QWidget *parent = nullptr);

    int timestamp();
    NoteType noteType(); //TODO : add to uml
    int maxHits();
    int points();
    int timeout();
    void hit();
    void paint(QPainter *,const QStyleOptionGraphicsItem *,QWidget *) override;

private:
    int _timestamp;
    NoteType _noteType; //TODO : add to uml
    int _maxHits;
    int _points;
    int _timeout;
    QPixmap** _frames;
    int _hits;
};

#endif // NOTE_H
