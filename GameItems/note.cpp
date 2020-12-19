#include "note.h"
#include <QPixmap>
#include <QPainter>
#include <QWidget>
#include <QStyleOptionGraphicsItem>
#include <QDebug>
#include <QRandomGenerator>

Note::Note(NoteType type, int timestamp, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), _noteType(type), _timestamp(timestamp)
{
    _countPaint = _framesNb = 0;
    quint32 rand = QRandomGenerator::global()->bounded(1, 4);;

    switch (_noteType)
    {
    case NoteType::BONUS:
        sprite = new QPixmap(":/img/Bonus(32x32).png");
        _frameWidth = 32;
        _frameHeight = 32;
        _maxFrame = 17;
        break;
    case NoteType::TRAP:
        sprite = new QPixmap(":/img/Trap(38x38).png");
        _frameWidth = 38;
        _frameHeight = 38;
        _maxFrame = 8;
        break;
    case NoteType::SMASH:
        sprite = new QPixmap(":/img/Enemie/Smash/Rock(42x42).png");
        _frameWidth = 42;
        _frameHeight = 42;
        _maxFrame = 4;
        break;
    case NoteType::NORMALDOWN:
        switch (rand)
        {
        case 1:
            sprite = new QPixmap(":/img/Enemie/Down/AngryPig(36x30).png");
            _frameWidth = 36;
            _frameHeight = 30;
            _maxFrame = 12;
            break;
        case 2:
            sprite = new QPixmap(":/img/Enemie/Down/Slime(44x30).png");
            _frameWidth = 44;
            _frameHeight = 30;
            _maxFrame = 10;
            break;
        case 3:
            sprite = new QPixmap(":/img/Enemie/Down/Turtle(44x26).png");
            _frameWidth = 44;
            _frameHeight = 26;
            _maxFrame = 8;
        break;
        default:
            qDebug() << "Not in range";
            break;
        }
        break;
    case NoteType::NORMALUP:
        switch (rand)
        {
        case 1:
            sprite = new QPixmap(":/img/Enemie/Up/Bat(46x30).png");
            _frameWidth = 46;
            _frameHeight = 30;
            _maxFrame = 7;
            break;
        case 2:
            sprite = new QPixmap(":/img/Enemie/Up/Bird(32x32).png");
            _frameWidth = 32;
            _frameHeight = 32;
            _maxFrame = 9;
            break;
        case 3:
            sprite = new QPixmap(":/img/Enemie/Up/Ghost(44x30).png");
            _frameWidth = 44;
            _frameHeight = 30;
            _maxFrame = 10;
            break;
        default:
            qDebug() << "Not in range :" << rand;
            break;
        }
        break;
    default:
        qDebug() << "Wrong type of note :" << _noteType;
        break;
    }
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
    painter->drawPixmap(10, 10, 80, 80, *sprite, _framesNb * _frameWidth, 0, _frameWidth, _frameHeight);
    _countPaint++;
    if(_countPaint >= 20)
    {
        _framesNb++;
        _countPaint = 0;
    }
    if(_framesNb >= _maxFrame)
        _framesNb = 0;
}

