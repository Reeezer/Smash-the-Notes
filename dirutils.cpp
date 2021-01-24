#include "dirutils.h"
#include "fileutils.h"
#include "song.h"

#include <QDebug>
#include <QDir>

void getSongList(QString path, QList<Song *> *songlist)
{
    qDebug() << "reading songs directory at '" + path + "'";

    QDir songdir(path);
    for (QString dirpath : songdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot))
    {
        qDebug() << "dir found: " << dirpath;
        QDir dir(path + QDir::separator() + dirpath);

        QStringList foundFiles = dir.entryList(QStringList("*.osu"), QDir::Files);
        if (foundFiles.size() > 0)
        {
            QString osufilename = foundFiles[0];
            qDebug() << "found osu file: " << osufilename;

            QString absoluteBasePath = path + QDir::separator() + dirpath;

            /* La classe song se charge elle-même de construire les autres chemins d'accès */
            Song *song = new Song(absoluteBasePath, osufilename);
            qDebug() << "new song with osu file set to: " << song->getPath();
            qDebug() << "audio file path set to: " << song->getAudioFilePath();
            qDebug() << "highscore file path set to: " << song->getHighscoreFilePath();

            songlist->append(song);
        }
    }
}
