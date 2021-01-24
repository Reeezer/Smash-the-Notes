#ifndef SONGITEM_H
#define SONGITEM_H

#include <QListWidgetItem>

class Song;

class SongItem : public QListWidgetItem
{
public:
    SongItem(QListWidget *parent = nullptr);
    SongItem(Song *, QListWidget *parent = nullptr);

    /* getters */
    Song *getSong();

private:
    Song *_song;
};

#endif // SONGITEM_H
