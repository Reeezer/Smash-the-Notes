#pragma once

#include <QWidget>
#include <QLabel>
#include <QListWidget>

#include "song.h"

class SongDetails : public QWidget
{
public:
    SongDetails(QWidget *parent = nullptr);

public slots:
    void setSongDetails(Song*);

private:
    QLabel *titleLabel;
    QLabel *highscoreLabel;
    QLabel *rankLabel;

    QListWidget *highscoreList;
};
