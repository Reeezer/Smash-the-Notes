#include "songitem.h"

SongItem::SongItem(QListWidget *parent)
    :QListWidgetItem(parent)
{

}

Song* SongItem::getSong()
{
    return song;
}
