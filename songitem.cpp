#include "songitem.h"
#include "song.h"

SongItem::SongItem(QListWidget *parent)
    :QListWidgetItem(parent)
{}

SongItem::SongItem(Song *song, QListWidget *parent)
    : QListWidgetItem(parent), _song(song)
{
    setText(song->getArtist() + " - " + song->getTitle());
}

Song* SongItem::getSong()
{
    return _song;
}
