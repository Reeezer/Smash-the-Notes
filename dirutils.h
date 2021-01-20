#ifndef DIRUTILS_H
#define DIRUTILS_H

#include "song.h"

#include <QList>
#include <QDir>
#include <QDebug>

void getSongList(QString, QList<Song *> *);

#endif // DIRUTILS_H
