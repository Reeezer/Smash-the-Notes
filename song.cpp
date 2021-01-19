#include "song.h"

Song::Song()
{}

Song::Song(QString title, QString artist, QString path, QString audioFilePath, QString highscoreFilePath)
    : _title(title), _artist(artist), _path(path), _audioFilePath(audioFilePath), _highscoreFilePath(highscoreFilePath)
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

QString Song::getHighscoreFilePath()
{
    return _highscoreFilePath;
}

QString Song::getArtist()
{
    return _artist;
}

QString Song::getTitle()
{
    return _title;
}

int Song::getPlayCount()
{
    return _highscores.size();
}

int Song::getHighscore()
{
    if (_highscores.size() > 0)
        return _highscores[0];
    else
        return -1;
}

void Song::setRank(Rank rank)
{
    _rank = rank;
}

void Song::setHighscores(QList<int> scores)
{
    for (int score : scores)
        _highscores.append(score);
}
