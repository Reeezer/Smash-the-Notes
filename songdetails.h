#pragma once

#include <QWidget>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>

#include "song.h"

class SongDetails : public QWidget
{
    Q_OBJECT

public:
    SongDetails(QWidget *parent = nullptr);

public slots:
    void setSongDetails(Song*);

signals:
    void displayMainMenu();

private:
    QLabel *_titleLabel;
    QLabel *_highscoreLabel;
    QLabel *_rankLabel;
    QPushButton *_returnButton;

    QListWidget *_highscoreList;
};
