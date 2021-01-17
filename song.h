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
    Song(QString);

    Rank getRank();
    QString getPath();

private:
    Rank _rank;
    QString _path;
};

#endif // SONG_H
