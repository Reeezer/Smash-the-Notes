#include "song.h"

Song::Song()
{}

Song::Song(QString title, QString path) : _title(title),  _path(path)
{}

Rank Song::getRank()
{
    return _rank;
}

QString Song::getPath()
{
    return _path;
}

QString Song::getTitle()
{
    return _title;
}
