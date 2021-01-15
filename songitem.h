#ifndef SONGITEM_H
#define SONGITEM_H

#include <QListWidgetItem>

class Song;

class SongItem : public QListWidgetItem
{
public:
    SongItem(QListWidget *parent = nullptr);

    Song* getSong();
private:
    Song* song;
};

#endif // SONGITEM_H
