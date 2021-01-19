#ifndef SONG_H
#define SONG_H

#include <QList>
#include <QString>

enum Rank
{
    D,
    C,
    B,
    A,
    S,
    SS,
    SSS
};

class Song
{
public:
    Song();
    Song(QString, QString, QString, QString);

    Rank getRank();
    QString getPath();
    QString getAudioFilePath();
    QString getArtist();
    QString getTitle();

private:
    Rank _rank;
    QString _title;
    QString _artist;
    QString _path;
    QString _audioFilePath;
};

#endif // SONG_H
