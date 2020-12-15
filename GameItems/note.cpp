#include "note.h"
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

Note::Note(NoteType type, int timestamp, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), _timestamp(timestamp), _noteType(type)
{

}

int Note::getTimestamp() {return _timestamp;}
NoteType Note::getNoteType() {return _noteType;}
int Note::getMaxHits() {return _maxHits;}
int Note::getPoints() {return _points;}
int Note::getTimeout() {return _timeout;}
int Note::getHit() {return _hits;}

void Note::hit() {_hits++;}

void Note::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    switch (_noteType)
    {
    case NoteType::BONUS:
        painter->drawPixmap(10,10,50,50,QPixmap(":/img/Notes.png"));
        break;
    case NoteType::TRAP:
        painter->drawPixmap(10,10,50,50,QPixmap(":/img/Trap2.png"));
        break;
    case NoteType::SMASH:
        painter->drawPixmap(10,10,50,50,QPixmap(":/img/Smash.png"));
        break;
    case NoteType::NORMAL:
        painter->drawPixmap(10,10,50,50,QPixmap(":/img/Enemie1.png"));
        break;
    default:
        qDebug() << "Wrong type of note";
        break;
    }
}

