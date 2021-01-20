#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QList>
#include <QMap>
#include <QString>

#include "gameitems/note.h"
#include "rank.h"

bool loadHighscoreFile(QString &, Rank *, QList<int> *);
bool writeHighscoreFile(QString &, Rank, QList<int> *);
bool loadOsuFile(QString& , QList<Note *> *, QList<Note *> *);
bool loadOsuFileMetadata(QString &, QMap<QString, QString> *);

#endif // FILEUTILS_H
