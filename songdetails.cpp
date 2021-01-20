#include "songdetails.h"
#include <QVBoxLayout>

SongDetails::SongDetails(QWidget *parent)
    : QWidget(parent)
{
    titleLabel = new QLabel;

    QVBoxLayout mainLayout(this);
    mainLayout.addWidget(titleLabel);
}

void SongDetails::setSongDetails(Song *song)
{
    titleLabel->setText(song->getArtist() + " - " + song->getTitle());
}
