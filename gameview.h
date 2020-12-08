#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QList>
#include <QGraphicsItem>
#include <QTimerEvent>

#include "game.h"
#include "GameItems/note.h"
//class Song; //TODO : change to include when Song is implemented

class GameView : public QGraphicsView
{
public:
    GameView(Game *game, QWidget *parent = nullptr);

private:
    Game *game;
    //Song *song;

    QGraphicsScene *scene;
    QMediaPlayer *music;
    //QSoundEffect *sounds;
    QList<Note *> upNotes;
    QList<Note *> downNotes;

    void loadSong(QString filename);
    void removeNote(QList<Note *> *);
    void update();
    void changeNotePosition(QList<Note *> *);
};

#endif // GAMEVIEW_H
