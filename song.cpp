#include "song.h"
#include "fileutils.h"

#include <QFileInfo>
#include <QDir>
#include <QDebug>

Song::Song()
{}

Song::Song(QString absoluteBasePath, QString osuFileName)
{
    _osuFilePath = absoluteBasePath + QDir::separator() + osuFileName;
    _highscoreFilePath = absoluteBasePath + QDir::separator() + "highscores.json";

    QMap<QString, QString> songMetadata;
    loadOsuFileMetadata(_osuFilePath, &songMetadata);

    _artist = songMetadata["Metadata/Artist"];
    _title = songMetadata["Metadata/Title"];
    _audioFilePath = absoluteBasePath + QDir::separator() + songMetadata["General/AudioFilename"];

    QFileInfo highscoreFileInfo(_highscoreFilePath);
    if (highscoreFileInfo.exists() && highscoreFileInfo.isFile()) {
        qDebug() << "found highscore file at " << _highscoreFilePath;
        loadHighscoreFile(_highscoreFilePath, &_rank, &_highscores);
    }
}

void Song::addHighscore(Rank rank, int score)
{
    /* n'effectuer l'ajout que si le score est plus haut */
    if (getHighscore() < score) {
        _highscores.insert(0, score);
        writeHighscoreFile(_highscoreFilePath, _rank, &_highscores);
    }
}

Rank Song::getRank()
{
    return _rank;
}

QString Song::getPath()
{
    return _osuFilePath;
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
