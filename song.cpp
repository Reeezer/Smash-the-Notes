#include "song.h"

Song::Song()
{}

Song::Song(QString title, QString artist, QString path, QString audioFilePath)
    : _title(title), _artist(artist), _path(path), _audioFilePath(audioFilePath)
{}

Rank Song::getRank()
{
    return _rank;
}

QString Song::getPath()
{
    return _path;
}

QString Song::getAudioFilePath()
{
    return _audioFilePath;
}

QString Song::getArtist()
{
    return _artist;
}

QString Song::getTitle()
{
    return _title;
}
