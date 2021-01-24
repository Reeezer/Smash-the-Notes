#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QList>
#include <QMap>
#include <QString>

#include "rank.h"

class GameData;
class Note;

bool loadHighscoreFile(QString &, Rank *, QList<int> *);
bool writeHighscoreFile(QString &, Rank, QList<int> *);
bool loadOsuFile(QString &, QList<Note *> *, QList<Note *> *);
bool loadOsuFileMetadata(QString &, QMap<QString, QString> *);
bool loadSettingsFile(QString &path, GameData *gamedata);
bool writeSettingsFile(QString &path, GameData *gamedata);

#endif // FILEUTILS_H
