#include "song.h"
#include "fileutils.h"

#include <QFileInfo>
#include <QDebug>

Song::Song()
{}

Song::Song(QString title, QString artist, QString path, QString audioFilePath, QString highscoreFilePath)
    : _title(title), _artist(artist), _path(path), _audioFilePath(audioFilePath), _highscoreFilePath(highscoreFilePath)
{
    QFileInfo highscoreFileInfo(_highscoreFilePath);
    if (highscoreFileInfo.exists() && highscoreFileInfo.isFile()) {
        qDebug() << "found highscore file at " << _highscoreFilePath;
        loadHighscoreFile(_highscoreFilePath, &_rank, &_highscores);
    }
}

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

void Song::addHighscore(Rank rank, int score)
{
    /* n'effectuer l'ajout que si le score est plus haut */
    if (getHighscore() < score) {
        _highscores.insert(0, score);
        writeHighscoreFile(_highscoreFilePath, _rank, &_highscores);
    }
}
