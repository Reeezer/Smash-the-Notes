#include "song.h"

Song::Song()
{}

Song::Song(QString path) : _path(path)
{}

Rank Song::getRank()
{
    return _rank;
}

QString Song::getPath()
{
    return _path;
}
