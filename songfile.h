#ifndef SONGFILE_H
#define SONGFILE_H

#include <QList>
#include <QMap>
#include <QString>

#include "GameItems/note.h"

bool loadFromFile(QString& , QList<Note *> *, QList<Note *> *);

#endif // SONGFILE_H
