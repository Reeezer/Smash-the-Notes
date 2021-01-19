#ifndef SONG_H
#define SONG_H

#include <QList>
#include <QString>

#include "rank.h"

class Song
{
public:
    Song();
    Song(QString, QString);

    Rank getRank();
    QString getPath();
    QString getAudioFilePath();
    QString getArtist();
    QString getTitle();
    QString getHighscoreFilePath();
    int getPlayCount();
    int getHighscore();

    void addHighscore(Rank, int);

private:
    Rank _rank;
    QString _title;
    QString _artist;
    QString _osuFilePath;
    QString _audioFilePath;
    QString _highscoreFilePath;
    QList<int> _highscores;
};

#endif // SONG_H
