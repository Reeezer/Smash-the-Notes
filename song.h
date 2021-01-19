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
    Song(QString, QString);

    Rank getRank();
    QString getPath();
    QString getTitle();

private:
    Rank _rank;
    QString _title;
    QString _path;
};

#endif // SONG_H
