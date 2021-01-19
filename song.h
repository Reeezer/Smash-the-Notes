#ifndef SONG_H
#define SONG_H

#include <QList>
#include <QString>

#include "rank.h"

class Song
{
public:
    Song();
    Song(QString, QString, QString, QString, QString);

    Rank getRank();
    QString getPath();
    QString getAudioFilePath();
    QString getArtist();
    QString getTitle();
    QString getHighscoreFilePath();
    int getPlayCount();
    int getHighscore();


    void setRank(Rank);
    void setHighscores(QList<int>);


private:
    Rank _rank;
    QString _title;
    QString _artist;
    QString _path;
    QString _audioFilePath;
    QString _highscoreFilePath;
    QList<int> _highscores;
};

#endif // SONG_H
