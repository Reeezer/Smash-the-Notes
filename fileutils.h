#pragma once

#include <QList>
#include <QMap>
#include <QString>

#include "GameItems/note.h"

bool loadOsuFile(QString& , QList<Note *> *, QList<Note *> *);
bool loadOsuFileMetadata(QString &, QMap<QString, QString> *);
