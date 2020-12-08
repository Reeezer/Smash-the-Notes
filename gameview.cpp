#include "gameview.h"

GameView::GameView(Game *game, QWidget *parent)
    : QGraphicsView(parent), game(game)
{
    this->setScene(scene);
    this->setVerticalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy (Qt::ScrollBarAlwaysOff);
}

void GameView::loadSong(QString filename)
{

}

void GameView::removeNote(QList<Note *> *list)
{
    scene->removeItem(list->first());
    Note *temp = list->takeFirst();
    delete temp;
}

void GameView::update()
{
    changeNotePosition(&upNotes);
    changeNotePosition(&downNotes);
}

void GameView::changeNotePosition(QList<Note *> *list)
{
    for (int i = 0; i < list->count(); i++)
    {
        list->at(i)->setX(100 + ((list->at(i)->timestamp()-music->position()) * ((double)(this->width()-100)/(double)3000)));
        if(list->at(i)->x() <= 0)
        {
            removeNote(list);
        }
    }
}
