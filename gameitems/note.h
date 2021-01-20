#ifndef NOTE_H
#define NOTE_H

#include <QGraphicsPixmapItem>

class QPixmap;
class QPainter;
class QWidget;
class QElapsedTimer;
class QStyleOptionGraphicsItem;

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

    int _timeStamp;
    int _timeOut;
    int _hits;
    int _frameHeight;
    int _maxFrame;
    int _framesNb;
    int _frameWidth;
    int _lastElapsed;

    QPixmap *_sprite;

    /* constantes */
    const int TIMEOUT = 80;
};

#endif // NOTE_H
