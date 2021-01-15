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

    Rank getRank();
    QString getPath();

private:
    Rank rank;
    QString path;
};

#endif // SONG_H
