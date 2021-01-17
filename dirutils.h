#ifndef SONGDIR_H
#define SONGDIR_H

#include "song.h"

#include <QList>
#include <QDir>
#include <QDebug>

void getSongList(QString, QList<Song *> *);

#endif // SONGDIR_H
