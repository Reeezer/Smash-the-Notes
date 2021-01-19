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
    Song(QString, QString, QString);

    Rank getRank();
    QString getPath();
    QString getArtist();
    QString getTitle();

private:
    Rank _rank;
    QString _title;
    QString _artist;
    QString _path;
};

#endif // SONG_H
