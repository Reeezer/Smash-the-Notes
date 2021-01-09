#ifndef GAME_H
#define GAME_H

#include "animatable.h"
#include "GameItems/character.h"

#include <QFont>

class QPixmap;
class QString;
class QSoundEffect;

enum SoundEffectIndex {

};

enum SpriteIndex {

};

enum FontType {
    NORMAL_SMALL,
    NORMAL_LARGE,
    ACCURACY,
    FONT_ESIZE
};

struct Game
{
    int delay;
    int volume;

    QPixmap **sprites;
    QSoundEffect **soundEffects;

    // FIXME work in progress starts here
    QFont fonts[FONT_ESIZE];
    Animatable player[CHARACTERACTION_ESIZE];
};

bool loadRessources(Game *);

#endif // GAME_H
