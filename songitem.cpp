#include "songitem.h"
#include "song.h"

SongItem::SongItem(QListWidget *parent)
    :QListWidgetItem(parent)
{}

SongItem::SongItem(Song *song, QListWidget *parent)
    : QListWidgetItem(parent), _song(song)
{
    /* pas super propre mais c'est le seul moyen que j'ai trouvé pour avoir un espace devant,
     * margin-left: ne fonctionne pas, ni padding-left (ni rien en fait à part setSpacing qui
     * lui ajoute un espace mais sans aggrandir l'effet de sélection derrière donc c'est moche)*/
    setText("  " + song->getArtist() + " - " + song->getTitle());
}

Song* SongItem::getSong()
{
    return _song;
}
