#include "song.h"

Song::Song()
{}

Song::Song(QString title, QString artist, QString path) : _title(title), _artist(artist), _path(path)
{}

Rank Song::getRank()
{
    return _rank;
}

QString Song::getPath()
{
    return _path;
}

QString Song::getArtist()
{
    return _artist;
}

QString Song::getTitle()
{
    return _title;
}
