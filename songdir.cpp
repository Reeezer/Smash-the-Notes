#include "songdir.h"

void getSongList (QString path, QList<Song *> *songlist)
{
    qDebug() << "reading songs directory at '" + path + "'";

    QDir songdir(path);
    for (QString dirpath : songdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        qDebug() << "dir found: " << dirpath;
        QDir dir(path + QDir::separator() + dirpath);

        QString osufilepath = dirpath + QDir::separator() + dir.entryList(QStringList("*.osu"), QDir::Files)[0];
        qDebug() << "found osu file: " << osufilepath;

        Song *song = new Song(path + QDir::separator() + osufilepath);
        qDebug() << "new song with osu file set to: " << song->getPath();

        songlist->append(song);
    }
}
