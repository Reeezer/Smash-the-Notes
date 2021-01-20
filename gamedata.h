#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QFont>

class QPixmap;
class QString;
class QSoundEffect;

enum FontType {
    NORMAL_18,
    NORMAL_70,
    NORMAL_40,
    NORMAL_50,
    ACCURACY,
    FONT_ESIZE
};

/* structure contenant les données communes à plusieurs parties du jeu comme les paramètres ou certaines ressources */
struct GameData
{
    int _delay;
    int _volume;

    QFont _fonts[FONT_ESIZE];
};

bool loadRessources(GameData *);

#endif // GAMEDATA_H
