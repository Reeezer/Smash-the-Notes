#include "dirutils.h"
#include "fileutils.h"

void getSongList (QString path, QList<Song *> *songlist)
{
    qDebug() << "reading songs directory at '" + path + "'";

    QDir songdir(path);
    for (QString dirpath : songdir.entryList(QDir::Dirs | QDir::NoDotAndDotDot)) {
        qDebug() << "dir found: " << dirpath;
        QDir dir(path + QDir::separator() + dirpath);

        QStringList foundFiles = dir.entryList(QStringList("*.osu"), QDir::Files);
        if(foundFiles.size() > 0) {
            QString osufilepath = dirpath + QDir::separator() + foundFiles[0];
            qDebug() << "found osu file: " << osufilepath;

            QString absoluteOsuFilePath = path + QDir::separator() + osufilepath;

            QMap<QString, QString> songMetadata;
            loadOsuFileMetadata(absoluteOsuFilePath, &songMetadata);

            QString artist = songMetadata["Metadata/Artist"];
            QString title = songMetadata["Metadata/Title"];
            QString absoluteAudioFilePath = path + QDir::separator() + dirpath + QDir::separator() + songMetadata["General/AudioFilename"];

            Song *song = new Song(title, artist, absoluteOsuFilePath, absoluteAudioFilePath);
            qDebug() << "new song with osu file set to: " << song->getPath();
            qDebug() << "audio file path set to: " << song->getAudioFilePath();

            songlist->append(song);
        }
    }
}
